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
#define DN2500F_CMD_GENERAL_STATUS_CHANGE 0x48
#define DN2500F_CMD_SEARCH 0x47
#define DN2500F_CMD_SCAN 0x46
#define DN2500F_CMD_OPEN_CLOSE 0x4a
#define DN2500F_CMD_KEY_CONTROL 0x57

#define DN2500F_CMD_CUEING 0x4d
#define DN2500F_CMD_TIME 0x49
#define DN2500F_CMD_TRACK_POSITION 0x44

/* Deck commands */
#define	DN2500F_DECK_CMD_LOAD_CD 0x42
#define	DN2500F_DECK_CMD_DRAWER 0x43
#define DN2500F_DECK_TRACK_POSITION 0x44
#define	DN2500F_DECK_CMD_CUE 0x45

/* Remote parameters */
#define DN2500F_PARAM_PLAYING 0x05
#define DN2500F_PARAM_STOPPED 0x09
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



typedef enum
{
    MODE_REMAIN = 1,
    MODE_ELAPSED = 2, /* ? */
} DN2500F_TIMEMODE;

typedef enum
{
    MODE_SINGLE = 0,
    MODE_CONTINUE = 4, /* ? */
} DN2500F_PLAYMODE;

typedef enum
{
    STATUS_NOT_LOADED = 2,
    STATUS_STOPPED = 9,
    STATUS_CUED = 4,
    STATUS_PAUSED = 3,
    STATUS_PLAYING = 5,
    STATUS_PAUSED_PLAYING = 6,
    STATUS_INVALID = 0xff,
} DN2500F_PLAYSTATUS;

typedef struct
{
    byte Minute;
    byte Second;
    byte Frame;
} DN2500F_TRIPLE_POS;

/* DN2500F packet */
typedef byte dn2500f_packet[DN2500F_PACKET_SIZE];
typedef dn2500f_packet *pdn2500f_packet;


/* Functions */
int dn2500f_init(const char *ComPort);
int dn2500f_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);
int dn2500f_start_cueing(byte Deck);
int dn2500f_cue(byte Deck, byte Minute, byte Second, byte Frame);
int dn2500f_unload(byte Deck);
int dn2500f_update_time(byte Deck);
int dn2500f_play(byte Deck);
int dn2500f_pause(byte Deck);


int dn2500f_set_current_time(byte Deck, byte Minutes, byte Seconds, byte Frames);
int dn2500f_set_play_mode(byte Deck, DN2500F_PLAYMODE Mode);
int dn2500f_set_time_mode(byte Deck, DN2500F_TIMEMODE Mode);

DN2500F_PLAYSTATUS dn2500f_get_deck_play_stats(byte Deck);

#endif /* !_DN2500F_H */