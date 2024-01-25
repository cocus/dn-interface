#ifndef _INTERFACE_H
#define _INTERFACE_H

/*
* This file contains interface types and function prototypes.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#include <Windows.h>
#include "global.h"
#include "dn2000f.h"



/* Internal interface functions */
void DoPlayPause(byte Deck);
void DoCue(byte Deck);
void DoPitchChange(byte Deck, byte Pitch);
void DoTimeMode(byte Deck, byte Mode);
void DoSearch(byte Deck, byte Speed);
void DoScan(byte Deck, byte Speed);

/* Var to hold the current time mode for the decks, either PARAM_ELAPSED or PARAM_REMAIN */
byte TimeMode[2];

/* Var to hold the current play mode for the decks, either PARAM_SINGLE or PARAM_CONTINUE */
byte PlayMode[2];

/* Var to hold the current play state for the decks, either PARAM_PLAYING or PARAM_PAUSED */
byte PlayState[2];

/* Var to hold the current cue state for the decks. True if the deck is cued else false */
bool CueState[2];

/* Var to hold the current pitch range for the decks, either Four, Eight or Sixteen */
enum dn_pitch_range PitchRange[2];

#endif /* !_INTERFACE_H */
