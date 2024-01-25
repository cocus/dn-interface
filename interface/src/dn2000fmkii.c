/*
* Comms to the Denon DN2000F mk II RC-35B.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#define LOG

#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>

#include "dn2000fmkii.h"
#include "log.h"
#include "interface.h"
#include "comms.h"
#include "bcd.h"

void dn2000fmkii_process_packet(ppacket packet);

int dn2000fmkii_init(char *ComPort)
{
	comms_init(ComPort, DN2000FMKII_BAUD_RATE, DN2000FMKII_PACKET_SIZE, dn2000fmkii_process_packet);

	/* Clear the deck states */
	TimeMode[0] = DN2000FMKII_PARAM_ELAPSED;
	TimeMode[1] = DN2000FMKII_PARAM_ELAPSED;
	PlayState[0] = DN2000FMKII_PARAM_PAUSED;
	PlayState[1] = DN2000FMKII_PARAM_PAUSED;
	CueState[0] = false;
	CueState[1] = false;
	dn2000fmkii_unload(0);
	dn2000fmkii_unload(1);
	return ERR_OK;
}

void dn2000fmkii_process_packet(ppacket packet)
{
	/* Common packet info:
	p->a: The deck number, either 1 or 2.
	p->b: The command.
	*/

//	dn2000fmkii_packet packet = *p;

	switch (packet[1]) {
	case DN2000FMKII_CMD_PITCH:
		DoPitchChange(packet[0], packet[2]); /* c: Pitch value */
		break;

	case DN2000FMKII_CMD_PLAY_PAUSE:
		DoPlayPause(packet[0]);
		break;

	case DN2000FMKII_CMD_CUE:
		DoCue(packet[0]);
		break;

	case DN2000FMKII_CMD_TIME:
		DoTimeMode(packet[0], packet[2]); /* c: Time mode */
		break;

	case DN2000FMKII_CMD_SEARCH:
		DoSearch(packet[0], packet[2]); /* c: Search value */
		break;

	case DN2000FMKII_CMD_SCAN:
		DoScan(packet[0], packet[2]); /* c: Scan value */
		break;
	}
}

int dn2000fmkii_cue(byte Deck, byte Minute, byte Second, byte Frame)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Send a "going to cue point" packet to the remote. This flashes the Cue light. */
	dn2000fmkii_packet packet = { 0 };
	packet[0] = DN2000FMKII_CMD_CUEING;
	packet[1] = Deck;
	packet[2] = DN2000FMKII_PARAM_PAUSED;
	comms_send((ppacket)&packet);

    /* The cue has been completed. Update the time display. This sets the Cue light to solid. */
	dn2000fmkii_update_time(Deck, Minute, Second, Frame, true, true, false, false);

	return ERR_OK;
}

int dn2000fmkii_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;
	
	/* Send the full "disc" time to the remote. */
	dn2000fmkii_packet packet = { 0 };
	packet[0] = DN2000FMKII_CMD_TOTAL_DURATION;
	packet[1] = Deck;
	packet[2] = 0x01;
	packet[3] = 0x01; /* Always one track */
	packet[4] = to_bcd(DurationMinutes); /*                                  */
	packet[5] = to_bcd(DurationSeconds); /* The duration must be sent as BCD */
	packet[6] = to_bcd(DurationFrames);  /*                                  */
	packet[7] = 0x01;
	comms_send((ppacket)&packet);

	return ERR_OK;
}

int dn2000fmkii_play(byte Deck)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Clear the cue state. */
	dn2000fmkii_packet packet = { 0 };
	packet[0] = DN2000FMKII_CMD_CUEING;
	packet[1] = Deck;
	packet[2] = 0x01;
	comms_send((ppacket)&packet);

	return ERR_OK;
}

int dn2000fmkii_pause(byte Deck)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Set the cue state */
	dn2000fmkii_packet packet = { 0 };
	packet[0] = DN2000FMKII_CMD_CUEING;
	packet[1] = Deck;
	packet[2] = DN2000FMKII_PARAM_PAUSED;

	comms_send((ppacket)&packet);

	return ERR_OK;
}

int dn2000fmkii_update_time(byte Deck, byte Minute, byte Second, byte Frame, bool IsLoaded, bool IsCued, bool IsPaused, bool IsPlaying)
{	
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Set the time display */
	dn2000fmkii_packet packet = { 0 };
	packet[0] = DN2000FMKII_CMD_TRACK_POSITION;
	packet[1] = Deck;
	packet[2] = TimeMode[Deck - 1];

	if (IsLoaded)
	{
		packet[3]= DN2000FMKII_PARAM_TRACK_1;
		packet[4] = to_bcd(Minute);
		packet[5] = to_bcd(Second);
		packet[6] = to_bcd(Frame);

		if (IsPlaying)
			packet[7] = DN2000FMKII_PARAM_PLAYING;
		else if (IsPaused)
			packet[7] = DN2000FMKII_PARAM_STOPPED;
		else if (IsCued)
		{
			packet[7] = DN2000FMKII_PARAM_STOPPED;
			packet[8] = DN2000FMKII_PARAM_CUED;
		}
	}
	else
	{
		packet[3] = DN2000FMKII_PARAM_NO_TRACK;
		packet[4] = DN2000FMKII_PARAM_NO_TIME;
		packet[5] = DN2000FMKII_PARAM_NO_TIME;
		packet[6] = DN2000FMKII_PARAM_NO_TIME;
	}

	comms_send((ppacket)&packet);

	return ERR_OK;
}


int dn2000fmkii_unload(byte Deck)
{
	if (Deck != 0 && Deck != 1)
		return ERR_INVALID_DECK;

	return ERR_OK;
}

