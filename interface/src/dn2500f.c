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



void dn2500f_checksum(dn2500f_packet packet)
{
	unsigned short checksum =
		packet[0] + packet[1] + packet[2] + packet[3] + packet[4] + packet[5] +
		packet[6] + packet[7] + packet[8] + packet[9] + packet[10];
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

	dn2500f_packet *pkt = packet;

	switch (packet[1]) {
	case DN2500F_CMD_PITCH:
		DoPitchChange(packet[0], packet[4]); /* 4: Pitch value */
		break;

	case DN2500F_CMD_PLAY:
	case DN2500F_CMD_PAUSE:
		DoPlayPause(packet[0]);
		break;
	case DN2500F_CMD_OPEN_CLOSE:
		DoOpenClose(packet[0]);
		break;

	case DN2500F_CMD_CUE:
		DoCue(packet[0]);
		break;

	case DN2500F_CMD_TIME:
		DoTimeMode(packet[0], packet[2]); /* c: Time mode */
		break;

	case DN2500F_CMD_SEARCH:
		DoSearch(packet[0], packet[2]); /* c: Search value */
		break;

	case DN2500F_CMD_SCAN:
		DoScan(packet[0], packet[2]); /* c: Scan value */
		break;

	case DN2500F_CMD_TRACK_CHANGE:
		/* index mode:
		  packet[2] = 0x10 next, 0x11 prev
		  packet[3] always 0x01
		  packet[4] = 2 first digits (bcd) of index
		  normal mode:
		  packet[2] always 0x01
		  packet[3] = 0x02 next, 0x12 previous, 0x04 previous (unloaded), 0x05 next (unloaded)
		*/
		if (packet[2] == 0x01)
			DoTrackChange(packet[0], packet[3] == 0x12 ? 0 : 1);
		else if (packet[2] == 0x00) // this happens when the deck is not loaded I think?
			DoTrackChange(packet[0], packet[3] == 0x04 ? 0 : 1);
		else
			DoIndexChange(packet[0], packet[4], packet[2] == 0x11 ? 0 : 1);
		break;

	case DN2500F_CMD_GENERAL_STATUS_CHANGE:
		DoReverse(packet[0]);
		break;
	case DN2500F_CMD_KEY_CONTROL:
		DoKeyChange(packet[0], packet[2], packet[3], packet[2] == 1 ? packet[4] : 0); // packet[2] = 0 => off, 1 = custom (see packet[4]), 2 = automatic
		break;
	}
}



typedef enum
{
    NO_INIT = 0,
    NOT_LOADED,
    LOADING_TRACK,
    CUEING,
    CUE_MODE,
    PLAY_MODE,
    PAUSE_WHILE_PLAYING_MODE,
} DN2500F_STATE;

struct DN2500_DECK
{
    DN2500F_STATE state;
    /* Var to hold the current time mode for the decks, either PARAM_ELAPSED or PARAM_REMAIN */
    DN2500F_TIMEMODE TimeMode;
    /* Var to hold the current play mode for the decks, either PARAM_SINGLE or PARAM_CONTINUE */
    DN2500F_PLAYMODE PlayMode;
    /* Var to hold the current play state for the decks, either PARAM_PLAYING or PARAM_PAUSED */
    DN2500F_PLAYSTATUS PlayState;

    DN2500F_TRIPLE_POS CurrentPosition;
    byte CurrentTrack;

    DN2500F_TRIPLE_POS TotalLength;
    byte TotalTracks;

} decks[2] =
{ {NO_INIT, MODE_REMAIN, MODE_SINGLE, STATUS_NOT_LOADED, { DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME}, DN2500F_PARAM_NO_TRACK, { DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME}, DN2500F_PARAM_NO_TRACK },
  {NO_INIT, MODE_REMAIN, MODE_SINGLE, STATUS_NOT_LOADED, { DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME }, DN2500F_PARAM_NO_TRACK, { DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME, DN2500F_PARAM_NO_TIME }, DN2500F_PARAM_NO_TRACK } };

bool dn2500f_cmd42(byte Deck, byte arg1, byte NumTracks, byte TotalMinutes, byte TotalSeconds, byte TotalFrames)
{
    dn2500f_packet packet = { 0 };
    packet[0] = Deck;
    packet[1] = DN2500F_DECK_CMD_LOAD_CD;
    packet[2] = arg1; /* ???? */
    packet[3] = to_bcd(NumTracks); /* num tracks? */
    packet[4] = to_bcd(TotalMinutes);
    packet[5] = to_bcd(TotalSeconds);
    packet[6] = to_bcd(TotalFrames);

    packet[7] = 0x0d; /* ???? */
    packet[8] = 0x2f; /* ???? */

    dn2500f_checksum(packet);
    return SendRaw((byte*)&packet);
}

bool dn2500f_cmd43(byte Deck, byte arg1, byte arg2)
{
    dn2500f_packet packet = { 0 };
    packet[0] = Deck;
    packet[1] = DN2500F_DECK_CMD_DRAWER;
    packet[2] = arg1; /* play status */
    packet[3] = arg2; /* ???? */

    dn2500f_checksum(packet);
    return SendRaw((byte*)&packet);
}

bool dn2500f_cmd44(byte Deck, DN2500F_PLAYSTATUS Status, DN2500F_TIMEMODE ElapsedRemain, DN2500F_PLAYMODE SingleCont, byte TrackNum, byte Minute, byte Second, byte Frame)
{
    dn2500f_packet packet = { 0 };
    packet[0] = Deck;
    packet[1] = DN2500F_CMD_TRACK_POSITION;
    packet[2] = (byte)Status;
    packet[3] = (byte)ElapsedRemain | (byte)SingleCont;
    packet[4] = TrackNum;
    packet[5] = Minute;
    packet[6] = Second;
    packet[7] = Frame;

    // TODO: move this to update_time
    if (Status == STATUS_PAUSED)
    {
        packet[8] = 0x80;
        packet[9] = 0x6;
    }
    else if (Status == STATUS_CUED)
    {
        packet[8] = 0x80;
    }
    else if (Status == STATUS_PLAYING)
    {
        packet[8] = 0x80;
        packet[9] = 0x20;
    }

    packet[10] = 0x1;
    dn2500f_checksum(packet);
    return SendRaw((byte*)&packet);
}

bool dn2500f_cmd45(byte Deck, byte arg1)
{
    dn2500f_packet packet = { 0 };
    packet[0] = Deck;
    packet[1] = DN2500F_DECK_CMD_CUE;
    packet[4] = arg1; /* ???? */

    dn2500f_checksum(packet);
    return SendRaw((byte*)&packet);
}

int dn2500f_init_deck(byte Deck)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    /* works on all states I think */
    decks[Deck - 1].TimeMode = MODE_REMAIN;
    decks[Deck - 1].PlayMode = MODE_SINGLE;
    decks[Deck - 1].PlayState = STATUS_STOPPED; //STATUS_NOT_LOADED; // don't send this, otherwise I can't get rid of it

    decks[Deck - 1].CurrentTrack = 1; // same as above DN2500F_PARAM_NO_TRACK;
    decks[Deck - 1].CurrentPosition.Minute = DN2500F_PARAM_NO_TIME;
    decks[Deck - 1].CurrentPosition.Second = DN2500F_PARAM_NO_TIME;
    decks[Deck - 1].CurrentPosition.Frame = DN2500F_PARAM_NO_TIME;

    decks[Deck - 1].state = NOT_LOADED;

    /* Assumption: The DN2500F can open switched on when the CD drawers are opened. The player might be sending a signal to the remote to tell it when the drawers are closed.
    *
    *  The packet is not fully understood at the moment, but sending the command to the remote seems to satifsy it to accept further commands.
    */

    /*
    * Turns the M logo off, and seems to reset everything.
    * $02 $43 $01 $00 $00 $00 $00 $00 $00 $00 $00 $00 $46
    */
    dn2500f_cmd43(Deck, 0x1, 0x0);
    Sleep(20);

    /* $02 $43 $09 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4E */
    dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0x0); /* not sure */
    Sleep(20);

    /* $02 $44 $09 $01 $01 $FF $FF $FF $00 $00 $01 $03 $4F */
    dn2500f_cmd44(Deck, decks[Deck - 1].PlayState, decks[Deck - 1].TimeMode, decks[Deck - 1].PlayMode, to_bcd(decks[Deck - 1].CurrentTrack), 0xff, 0xff, 0xff);
    Sleep(20);


    return ERR_OK;
}

int dn2500f_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    /* only possible when the deck is not already loaded */
    if (decks[Deck - 1].state != NOT_LOADED)
        return ERR_INVALID_STATE;

    /* switch to PAUSED */
    decks[Deck - 1].PlayState = STATUS_PAUSED;
    decks[Deck - 1].state = LOADING_TRACK;

    decks[Deck - 1].CurrentTrack = 1;
    decks[Deck - 1].TotalTracks = 1;

    decks[Deck - 1].TotalLength.Minute = DurationMinutes;
    decks[Deck - 1].TotalLength.Second = DurationSeconds;
    decks[Deck - 1].TotalLength.Frame = DurationFrames;

    /* turns M (cmd total duration): $02 $42 $01 $12 $78 $32 $07 $0D $2F $00 $00 $01 $44 */
    dn2500f_cmd42(Deck, 0x1, /* num tracks */decks[Deck - 1].TotalTracks, decks[Deck - 1].TotalLength.Minute, decks[Deck - 1].TotalLength.Second, decks[Deck - 1].TotalLength.Frame);

    /* CMD43(03, 0): PLAY led OFF, STOP led OFF: $02 $43 $03 $00 $00 $00 $00 $00 $00 $00 $00 $00 $48 */
    dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0);

    /* $02 $44 $03 $01 $01 $FF $FF $FF $80 $06 $01 $03 $CF */
    dn2500f_cmd44(Deck, decks[Deck - 1].PlayState, decks[Deck - 1].TimeMode, decks[Deck - 1].PlayMode, decks[Deck - 1].CurrentTrack, 0xff, 0xff, 0xff);

    return ERR_OK;
}

int dn2500f_start_cueing(byte Deck)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    if (decks[Deck - 1].state != LOADING_TRACK && decks[Deck - 1].state != PAUSE_WHILE_PLAYING_MODE) // TODO: maybe some other states allow cueing?
        return ERR_INVALID_STATE;


    decks[Deck - 1].PlayState = STATUS_CUED;

    /* CMD43(04, 0): PLAY led OFF, STOP led blinks: $02 $43 $04 $00 $00 $00 $00 $00 $00 $00 $00 $00 $49 */
    dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0);
    Sleep(50); // TBD

    if (decks[Deck - 1].state == LOADING_TRACK)
    {
        /* CMD43(04, 1): no changes from before: $02 $43 $04 $01 $00 $00 $00 $00 $00 $00 $00 $00 $4A */
        dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 1);
        Sleep(50); // TBD
    }
    else
    {
        /* CMD43(04, 0): PLAY led OFF, STOP led blinks: $02 $43 $04 $00 $00 $00 $00 $00 $00 $00 $00 $00 $49 */
        dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0);
        Sleep(50); // TBD
    }

    decks[Deck - 1].state = CUEING;

    /* $02 $44 $04 $01 $01 $08 $12 $19 $80 $00 $01 $01 $00 */
    dn2500f_cmd44(Deck, decks[Deck - 1].PlayState,
        decks[Deck - 1].TimeMode,
        decks[Deck - 1].PlayMode,
        to_bcd(decks[Deck - 1].CurrentTrack),
        to_bcd(decks[Deck - 1].CurrentPosition.Minute),
        to_bcd(decks[Deck - 1].CurrentPosition.Second),
        to_bcd(decks[Deck - 1].CurrentPosition.Frame));
    Sleep(50); // TBD

    return ERR_OK;
}

int dn2500f_cue(byte Deck, byte Minute, byte Second, byte Frame)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    if (decks[Deck - 1].state != CUEING) // TODO: maybe some other states allow cue?
        return ERR_INVALID_STATE;

    decks[Deck - 1].PlayState = STATUS_CUED;
    decks[Deck - 1].state = CUE_MODE;

    decks[Deck - 1].CurrentPosition.Minute = Minute;
    decks[Deck - 1].CurrentPosition.Second = Second;
    decks[Deck - 1].CurrentPosition.Frame = Frame;

    /* CMD43(04, 1): CMD43(04, 2): PLAY led OFF, STOP led ON (CUE mode): $02 $43 $04 $02 $00 $00 $00 $00 $00 $00 $00 $00 $4B */
    dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 2);
    Sleep(50); // TBD

    /* $02 $45 $00 $00 $02 $00 $00 $00 $00 $00 $00 $00 $49 */
    dn2500f_cmd45(Deck, 2);
    Sleep(50);

    /* $02 $44 $04 $01 $01 $08 $12 $19 $80 $00 $01 $01 $00 */
    dn2500f_cmd44(Deck, decks[Deck - 1].PlayState,
        decks[Deck - 1].TimeMode,
        decks[Deck - 1].PlayMode,
        to_bcd(decks[Deck - 1].CurrentTrack),
        to_bcd(decks[Deck - 1].CurrentPosition.Minute),
        to_bcd(decks[Deck - 1].CurrentPosition.Second),
        to_bcd(decks[Deck - 1].CurrentPosition.Frame));

    return ERR_OK;
}

int dn2500f_play(byte Deck)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    if (decks[Deck - 1].state != STATUS_CUED && decks[Deck - 1].state != PAUSE_WHILE_PLAYING_MODE) // TODO: maybe some other states allow play?
        return ERR_INVALID_STATE;

    decks[Deck - 1].PlayState = STATUS_PLAYING;
    decks[Deck - 1].state = PLAY_MODE;

    /* $02 $43 $05 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4A */
    dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0);
    Sleep(50); // TBD

    /* $02 $44 $05 $01 $01 $08 $12 $19 $80 $20 $01 $01 $21 */
    dn2500f_cmd44(Deck, decks[Deck - 1].PlayState,
        decks[Deck - 1].TimeMode,
        decks[Deck - 1].PlayMode,
        to_bcd(decks[Deck - 1].CurrentTrack),
        to_bcd(decks[Deck - 1].CurrentPosition.Minute),
        to_bcd(decks[Deck - 1].CurrentPosition.Second),
        to_bcd(decks[Deck - 1].CurrentPosition.Frame));

    return ERR_OK;
}

int dn2500f_pause(byte Deck)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    if (decks[Deck - 1].state != STATUS_PLAYING) // TODO: maybe some other states allow pausing?
        return ERR_INVALID_STATE;

    if (decks[Deck - 1].state == STATUS_PLAYING)
    {
        decks[Deck - 1].PlayState = STATUS_PAUSED_PLAYING;
        decks[Deck - 1].state = PAUSE_WHILE_PLAYING_MODE;

        /* $02 $43 $06 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4B */
        dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0);
        Sleep(50); // TBD

        /* $02 $44 $06 $01 $01 $08 $06 $10 $00 $00 $01 $00 $6D */
        dn2500f_cmd44(Deck, decks[Deck - 1].PlayState,
            decks[Deck - 1].TimeMode,
            decks[Deck - 1].PlayMode,
            to_bcd(decks[Deck - 1].CurrentTrack),
            to_bcd(decks[Deck - 1].CurrentPosition.Minute),
            to_bcd(decks[Deck - 1].CurrentPosition.Second),
            to_bcd(decks[Deck - 1].CurrentPosition.Frame));

        /* $02 $43 $06 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4B */
        dn2500f_cmd43(Deck, decks[Deck - 1].PlayState, 0);
        Sleep(50); // TBD

        /* $02 $45 $00 $00 $02 $00 $00 $00 $00 $00 $00 $00 $49 */
        dn2500f_cmd45(Deck, 2);
        Sleep(50);
    }
    else
    {
        return ERR_INVALID_STATE;
    }

    return ERR_OK;
}

int dn2500f_set_play_mode(byte Deck, DN2500F_PLAYMODE Mode)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    decks[Deck - 1].PlayMode = Mode;

    return dn2500f_update_time(Deck);
}

int dn2500f_set_time_mode(byte Deck, DN2500F_TIMEMODE Mode)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    decks[Deck - 1].TimeMode = Mode;

    return dn2500f_update_time(Deck);
}

int dn2500f_set_current_time(byte Deck, byte Minutes, byte Seconds, byte Frames)
{
    if (Deck != 1 && Deck != 2)
        return ERR_INVALID_DECK;

    decks[Deck - 1].CurrentPosition.Minute = Minutes;
    decks[Deck - 1].CurrentPosition.Second = Seconds;
    decks[Deck - 1].CurrentPosition.Frame = Frames;

    return dn2500f_update_time(Deck);
}

DN2500F_PLAYSTATUS dn2500f_get_deck_play_stats(byte Deck)
{
    if (Deck != 1 && Deck != 2)
        return STATUS_INVALID;

    return decks[Deck - 1].PlayState;
}

int dn2500f_update_time(byte Deck)
{
	if (Deck != 1 && Deck != 2)
		return ERR_INVALID_DECK;

    /* $02 $44 $06 $01 $01 $08 $06 $10 $00 $00 $01 $00 $6D */
    dn2500f_cmd44(Deck, decks[Deck - 1].PlayState,
        decks[Deck - 1].TimeMode,
        decks[Deck - 1].PlayMode,
        to_bcd(decks[Deck - 1].CurrentTrack),
        to_bcd(decks[Deck - 1].CurrentPosition.Minute),
        to_bcd(decks[Deck - 1].CurrentPosition.Second),
        to_bcd(decks[Deck - 1].CurrentPosition.Frame));

	return ERR_OK;
}

int dn2500f_init(const char* ComPort)
{
    comms_init(ComPort, DN2500F_BAUD_RATE, DN2500F_PACKET_SIZE, dn2500f_process_packet);
    
    /* Required for the remote to accept commands */
    if (dn2500f_init_deck(1) != ERR_OK)
        return ERR_MODEL_UNSUPPORTED;
    Sleep(50);

    if (dn2500f_init_deck(2) != ERR_OK)
        return ERR_MODEL_UNSUPPORTED;
    Sleep(50);

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
