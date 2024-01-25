/*
* Comms to the Denon DN2500F RC-44.
*
* Copyright 2010-2021 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#define LOG

#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>

#include "dn2500f.h"
#include "log.h"
#include "interface.h"
#include "comms.h"
#include "bcd.h"

void dn2500f_process_packet(ppacket packet);

int dn2500f_init(char *ComPort)
{
	comms_init(ComPort, DN2500F_BAUD_RATE, DN2500F_PACKET_SIZE, dn2500f_process_packet);

	/* Clear the deck states */
	TimeMode[0] = DN2500F_PARAM_ELAPSED;
	TimeMode[1] = DN2500F_PARAM_ELAPSED;
	PlayState[0] = DN2500F_PARAM_PAUSED;
	PlayState[1] = DN2500F_PARAM_PAUSED;
	CueState[0] = false;
	CueState[1] = false;

	/* Required for the remote to accept commands */
	return dn2500f_init_decks();
}

void dn2500f_checksum(dn2500f_packet packet)
{
//	dn2500f_packet p = packet;
	unsigned short checksum =
		packet[0] + packet[1] + packet[2] + packet[3] + packet[4] + packet[5] +
		packet[6] + packet[7] + packet[8] + packet[9] + packet[10];
//*p[0] += *p[1] += *p[2] += *p[3] += *p[4] += *p[5] +=
//*p[6] += *p[7] += *p[8] += *p[9] += *p[10];
	packet[11] = (byte)(checksum >> 8);
	packet[12] = (byte)checksum;
}

void dn2500f_process_packet(ppacket packet)
{
	/* Common packet info:
	p[0]: The deck number, either 1 or 2.
	p[1]: The command.

	p[11]: Checksum high (sum of all over bytes)
	p[12]: Checksum low (sum of all other bytes)
	*/

	//	dn2000fmkii_packet packet = *p;

	switch (packet[1]) {
	case DN2500F_CMD_PITCH:
		DoPitchChange(packet[0], packet[4]); /* 4: Pitch value */
		break;

	case DN2500F_CMD_PLAY:
	case DN2500F_CMD_PAUSE:
		DoPlayPause(packet[0]);
		break;

//	case DN2500FMKII_CMD_CUE:
//		DoCue(packet[0]);
//		break;

	case DN2500F_CMD_TIME:
		DoTimeMode(packet[0], packet[2]); /* c: Time mode */
		break;

	case DN2500F_CMD_SEARCH:
		DoSearch(packet[0], packet[2]); /* c: Search value */
//		break;
//
//	case DN2000FMKII_CMD_SCAN:
//		DoScan(packet[0], packet[2]); /* c: Scan value */
//		break;
	}
}


int dn2500f_cue(byte Deck, byte Minute, byte Second, byte Frame)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Send a "going to cue point" packet to the remote. This flashes the Cue light. */
	/* 01 45 00 00 02 00 00 00 00 00 00 00 48 */
	dn2500f_packet packet = { 0 };
	packet[0] = Deck;
	packet[2] = DN2500F_CMD_CUE;
	packet[4] = 0x02; /* ? */

	dn2500f_checksum(packet);
	comms_send((ppacket)&packet);

//	/* The cue has been completed. Update the time display. This sets the Cue light to solid. */
	dn2500f_update_time(Deck, Minute, Second, Frame, true, true, false, false);
//
	return ERR_OK;
}

int dn2500f_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Send the full "disc" time to the remote. */

	/* 0  1  2  3  4  5  6  7  8  9  10 11 12
	   01 42 01 01 18 49 66 02 02 00 00 01 10
	*/
	dn2500f_packet packet = { 0 };
	packet[0] = Deck;
	packet[1] = DN2500F_CMD_TOTAL_DURATION;
	packet[2] = 0x01;
	packet[3] = 0x01; /* Always one track */
	packet[4] = to_bcd(DurationMinutes); /*                                  */
	packet[5] = to_bcd(DurationSeconds); /* The duration must be sent as BCD */
	packet[6] = to_bcd(DurationFrames);  /*                                  */
	packet[7] = 0x02;
	packet[8] = 0x02;

	dn2500f_checksum(packet);
	comms_send((ppacket)&packet);

	return ERR_OK;
}
//
//int dn2000fmkii_play(byte Deck)
//{
//	if (Deck != 1 && Deck != 2)
//		return ERR_INVALID_DECK;
//
//	/* Clear the cue state. */
//	dn2000fmkii_packet packet = { 0 };
//	packet[0] = DN2000FMKII_CMD_CUEING;
//	packet[1] = Deck;
//	packet[2] = 0x01;
//	comms_send((ppacket)&packet);
//
//	return ERR_OK;
//}
//
//int dn2000fmkii_pause(byte Deck)
//{
//	if (Deck != 1 && Deck != 2)
//		return ERR_INVALID_DECK;
//
//	/* Set the cue state */
//	dn2000fmkii_packet packet = { 0 };
//	packet[0] = DN2000FMKII_CMD_CUEING;
//	packet[1] = Deck;
//	packet[2] = DN2000FMKII_PARAM_PAUSED;
//
//	comms_send((ppacket)&packet);
//
//	return ERR_OK;
//}

int dn2500f_update_time(byte Deck, byte Minute, byte Second, byte Frame, bool IsLoaded, bool IsCued, bool IsPaused, bool IsPlaying)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

	/* Set the time display */
	dn2500f_packet packet = { 0 };
	packet[0] = Deck;

	packet[1] = DN2500F_CMD_TRACK_POSITION;

//	packet[3] = TimeMode[Deck - 1];

	/* 
	  0  1  2  3  4  5  6  7  8  9  10 11 12 
	  01 44 05 03 01 18 45 29 00 20 01 00 F5 play
	  01 44 04 03 01 18 47 66 80 00 01 01 93 cued
	  */
	if (IsLoaded)
	{
		packet[4] = DN2500F_PARAM_TRACK_1;
		packet[5] = to_bcd(Minute);
		packet[6] = to_bcd(Second);
		packet[7] = to_bcd(Frame);

		if (IsPlaying)
			packet[2] = DN2500F_PARAM_PLAYING;
		else if (IsPaused)
			packet[7] = DN2500F_PARAM_PAUSED_PLAYING;
		else if (IsCued)
		{
			packet[7] = DN2500F_PARAM_STOPPED;
			packet[8] = DN2500F_PARAM_CUED;
		}

		packet[9] = 0x20; /* ? */
		packet[10] = 0x01; /* ? */
	}
	else
	{
		/* 
		0  1  2  3  4  5  6  7  8  9  10 11 12
		01 44 02 03 CC FF FF FF 00 00 CC 04 DF */
		packet[2] = 0x02; /* ? */
		packet[3] = TimeMode || PlayMode;
		packet[4] = DN2500F_PARAM_NO_TRACK;
		packet[5] = DN2500F_PARAM_NO_TIME;
		packet[6] = DN2500F_PARAM_NO_TIME;
		packet[7] = DN2500F_PARAM_NO_TIME;
		packet[10] = DN2500F_PARAM_NO_TRACK;
	}

	dn2500f_checksum(packet);
	comms_send((ppacket)&packet);

	return ERR_OK;
}


int dn2500f_init_decks()
{
	if (!dn2500f_init_deck(1))
		return ERR_DECK_INIT;

	if (!dn2500f_init_deck(2))
		return ERR_DECK_INIT;

	return ERR_OK;
}

int dn2500f_init_deck(byte Deck)
{
	/* Assumption: The DN2500F can open switched on when the CD drawers are opened. The player might be sending a signal to the remote to tell it when the drawers are closed.
	*
	*  The packet is not fully understood at the moment, but sending the command to the remote seems to satifsy it to accept further commands.
	*/

	dn2500f_packet packet = { 0 };
	packet[0] = Deck;
	packet[1] = DN2500F_DECK_CMD_DRAWER;
	packet[2] = 0x02; /* ? */
	packet[5] = 0x01; /* ? */

	dn2500f_checksum(packet);
	comms_send((ppacket)&packet);

	return ERR_OK;
}

//
//
//int dn2000fmkii_unload(byte Deck)
//{
//	if (Deck != 0 && Deck != 1)
//		return ERR_INVALID_DECK;
//
//	return ERR_OK;
//}
//
