#ifndef _DN2500F_H
#define _DN2500F_H

/*
* This file contains DN2500F function prototypes.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#include <Windows.h>

#include "dn2000f.h"

/* Protocol information */
#define DN2500F_BAUD_RATE 76677
#define DN2500F_PACKET_SIZE 13

/* Remote commands */
#define	DN2500F_CMD_TOTAL_DURATION 0x42
#define	DN2500F_CMD_TRACK_CHANGE 0x42
#define	DN2500F_CMD_PITCH 0x43
#define DN2500F_CMD_PLAY 0x44
#define DN2500F_CMD_CUE 0x45
#define DN2500F_CMD_PAUSE 0x4b
#define DN2500F_CMD_SEARCH 0x47
#define DN2500F_CMD_SCAN 0x46
#define DN2500F_CMD_OPEN_CLOSE 0x4a
#define DN2500F_CMD_OPEN_KEY 0x57

#define DN2500F_CMD_CUEING 0x4d
#define DN2500F_CMD_TIME 0x49
#define DN2500F_CMD_TRACK_POSITION 0x44

/* Deck commands */
#define	DN2500F_DECK_CMD_DRAWER 0x43

/* Remote parameters */
#define DN2500F_PARAM_PLAYING 0x05
#define DN2500F_PARAM_STOPPED 0xaa
#define DN2500F_PARAM_CUED 0xa0
#define DN2500F_PARAM_ELAPSED 0x00
#define DN2500F_PARAM_REMAIN 0x01
#define DN2500F_PARAM_SINGLE 0x01
#define DN2500F_PARAM_CONTINUE 0x02
#define DN2500F_PARAM_NO_TRACK 0xcc
#define DN2500F_PARAM_NO_TIME 0xff
#define DN2500F_PARAM_TRACK_1 0x01
#define DN2500F_PARAM_CUE_RELEASE 0x01
#define DN2500F_PARAM_PAUSED 0x03
#define DN2500F_PARAM_PAUSED_PLAYING 0x06


/* DN2500F packet */
typedef byte dn2500f_packet[DN2500F_PACKET_SIZE];
typedef dn2500f_packet *pdn2500f_packet;


/* Functions */
int dn2500f_init(char *ComPort);
int dn2500f_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);
int dn2500f_cue(byte Deck, byte Minute, byte Second, byte Frame);
int dn2500f_unload(byte Deck);
int dn2500f_update_time(byte Deck, byte Minute, byte Second, byte Frame, bool IsLoaded, bool IsCued, bool IsPaused, bool IsPlaying);
int dn2500f_play(byte Deck);
int dn2500f_pause(byte Deck);

#endif /* !_DN2500F_H */