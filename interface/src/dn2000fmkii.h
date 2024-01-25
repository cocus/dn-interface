#ifndef _DN2000FMKII_H
#define _DN2000FMKII_H

/*
* This file contains DN2000F mk II function prototypes.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#include <Windows.h>

#include "dn2000f.h"

/* Protocol information */
#define DN2000FMKII_BAUD_RATE 90566
#define DN2000FMKII_PACKET_SIZE 10

/* Remote commands */
#define	DN2000FMKII_CMD_TOTAL_DURATION 0x41
#define	DN2000FMKII_CMD_TRACK_CHANGE 0x42
#define	DN2000FMKII_CMD_PITCH 0x43
#define DN2000FMKII_CMD_PLAY_PAUSE 0x46
#define DN2000FMKII_CMD_SCAN 0x48
#define DN2000FMKII_CMD_SEARCH 0x49
#define DN2000FMKII_CMD_CUE 0x4c
#define DN2000FMKII_CMD_CUEING 0x4d
#define DN2000FMKII_CMD_TIME 0x50
#define DN2000FMKII_CMD_TRACK_POSITION 0x54
#define DN2000FMKII_CMD_OPEN_CLOSE 0x58

/* Remote parameters */
#define DN2000FMKII_PARAM_PLAYING 0x00
#define DN2000FMKII_PARAM_STOPPED 0xaa
#define DN2000FMKII_PARAM_CUED 0xa0
#define DN2000FMKII_PARAM_ELAPSED 0x01
#define DN2000FMKII_PARAM_REMAIN 0x02
#define DN2000FMKII_PARAM_NO_TRACK 0xdd
#define DN2000FMKII_PARAM_NO_TIME 0xff
#define DN2000FMKII_PARAM_TRACK_1 0x01
#define DN2000FMKII_PARAM_CUE_RELEASE 0x01
#define DN2000FMKII_PARAM_PAUSED 0x02

/* DN2000F mk II packet */
typedef byte dn2000fmkii_packet[DN2000FMKII_PACKET_SIZE];
typedef dn2000fmkii_packet *pdn2000fmkii_packet;

/* Functions */
int dn2000fmkii_init(char *ComPort);
int dn2000fmkii_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);
int dn2000fmkii_cue(byte Deck, byte Minute, byte Second, byte Frame);
int dn2000fmkii_unload(byte Deck);
int dn2000fmkii_update_time(byte Deck, byte Minute, byte Second, byte Frame, bool IsLoaded, bool IsCued, bool IsPaused, bool IsPlaying);
int dn2000fmkii_play(byte Deck);
int dn2000fmkii_pause(byte Deck);

#endif /* !_DN2000FMKII_H */