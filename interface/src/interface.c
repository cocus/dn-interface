/*
* Interface between external applications and the Denon DN2000F mk II RC-35B.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#include "interface.h"
#include "global.h"
#include "pitch.h"
#include "key.h"
#include "dn2000fmkii.h"
#include "dn2500f.h"
#include "dn-interface.h"

PitchChangeCallback _pitchchangecallbackhandler = 0;
TimeModeCallback _timemodecallbackhandler = 0;
PlayPauseCallback _playpausecallbackhandler = 0;
CueCallback _cuecallbackhandler = 0;
SearchCallback _searchcallbackhandler = 0;
ScanCallback _scancallbackhandler = 0;
OpenCloseCallback _openclosecallbackhandler = 0;
TrackChangeCallback _trackchangecallbackhandler = 0;
IndexChangeCallback _indexchangecallbackhandler = 0;
ReverseCallback _reversecallbackhandler = 0;
KeyChangeCallback _keychangecallbackhandler = 0;

byte _model = -1;

EXPORT_DECLSPEC int Init(const char *ComPort, byte Model)
{
	switch (Model)
	{
	case MODEL_DN2000F_MK_II:
		_model = Model;
		return dn2000fmkii_init(ComPort);

	case MODEL_DN2500F:
		_model = Model;
		return dn2500f_init(ComPort);
	}

	return ERR_MODEL_UNSUPPORTED;
}

EXPORT_DECLSPEC void SetPitchChangeCallback(PitchChangeCallback handler)
{
	_pitchchangecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetTimeModeCallback(TimeModeCallback handler)
{
	_timemodecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetPlayPauseCallback(PlayPauseCallback handler)
{
	_playpausecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetCueCallback(CueCallback handler)
{
	_cuecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetSearchCallback(SearchCallback handler)
{
	_searchcallbackhandler = handler;
}

EXPORT_DECLSPEC void SetScanCallback(SearchCallback handler)
{
	_scancallbackhandler = handler;
}

EXPORT_DECLSPEC void SetOpenCloseCallback(OpenCloseCallback handler)
{
	_openclosecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetTrackChangeCallback(TrackChangeCallback handler)
{
	_trackchangecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetIndexChangeCallback(IndexChangeCallback handler)
{
	_indexchangecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetReverseCallback(ReverseCallback handler)
{
	_reversecallbackhandler = handler;
}

EXPORT_DECLSPEC void SetKeyChangeCallback(KeyChangeCallback handler)
{
	_keychangecallbackhandler = handler;
}


EXPORT_DECLSPEC void Load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames)
{
	switch (_model)
	{
	case MODEL_DN2000F_MK_II:
		CueState[Deck - 1] = true;
		PlayState[Deck - 1] = DN2000FMKII_PARAM_PAUSED;

		dn2000fmkii_load(Deck, DurationMinutes, DurationSeconds, DurationFrames);

		if (TimeMode[Deck - 1] == DN2000FMKII_PARAM_ELAPSED)
			dn2000fmkii_cue(Deck, 0, 0, 0);
		else
			dn2000fmkii_cue(Deck, DurationMinutes, DurationSeconds, DurationFrames);
		break;

	case MODEL_DN2500F:
		CueState[Deck - 1] = true;
		PlayState[Deck - 1] = DN2500F_PARAM_PAUSED;

		dn2500f_load(Deck, DurationMinutes, DurationSeconds, DurationFrames);
		break;
		if (TimeMode[Deck - 1] == DN2500F_PARAM_ELAPSED)
			dn2500f_cue(Deck, 0, 0, 0);
		else
			dn2500f_cue(Deck, DurationMinutes, DurationSeconds, DurationFrames);
		break;
	}
}

EXPORT_DECLSPEC void Cue(byte Deck, byte Minute, byte Second, byte Frame)
{
	switch (_model)
	{
	case MODEL_DN2000F_MK_II:
		dn2000fmkii_cue(Deck, Minute, Second, Frame);
		break;
	case MODEL_DN2500F:
		dn2500f_cue(Deck, Minute, Second, Frame);
		break;
	}

	CueState[Deck - 1] = true;
}

EXPORT_DECLSPEC void UpdateTime(byte Deck, byte Minute, byte Second, byte Frame)
{
	switch (_model)
	{
	case MODEL_DN2000F_MK_II:
		dn2000fmkii_update_time(Deck, Minute, Second, Frame, true, CueState[Deck - 1], PlayState[Deck - 1] == DN2000FMKII_PARAM_PAUSED, PlayState[Deck - 1] == DN2000FMKII_PARAM_PLAYING);
		break;

	case MODEL_DN2500F:
		dn2500f_update_time(Deck, Minute, Second, Frame, true, CueState[Deck - 1], PlayState[Deck - 1] == DN2500F_PARAM_PAUSED, PlayState[Deck - 1] == DN2500F_PARAM_PLAYING);
		break;
	}
}

EXPORT_DECLSPEC void UpdateTimeMode(byte Deck, byte Mode)
{
	TimeMode[Deck - 1] = Mode;
}

EXPORT_DECLSPEC void Play(byte Deck)
{
	CueState[Deck - 1] = false;
	switch (_model)
	{
	case MODEL_DN2000F_MK_II:
		PlayState[Deck - 1] = DN2000FMKII_PARAM_PLAYING;
		dn2000fmkii_play(Deck);
		break;
	case MODEL_DN2500F:
		PlayState[Deck - 1] = DN2500F_PARAM_PLAYING;

		// TODO: impl
		break;
	}
}

EXPORT_DECLSPEC void Pause(byte Deck)
{
	CueState[Deck - 1] = false;
	switch (_model)
	{
	case MODEL_DN2000F_MK_II:
		PlayState[Deck - 1] = DN2000FMKII_PARAM_PLAYING;
		dn2000fmkii_pause(Deck);
		break;
	case MODEL_DN2500F:
		PlayState[Deck - 1] = DN2500F_PARAM_PAUSED;
		dn2500f_pause(Deck);
		break;
	}
}

void DoPlayPause(byte Deck)
{
	switch (_model)
	{
	case MODEL_DN2000F_MK_II:
		if (PlayState[Deck - 1] == DN2000FMKII_PARAM_PLAYING)
			dn2000fmkii_pause(Deck);
		else
			dn2000fmkii_play(Deck);
		break;
	case MODEL_DN2500F:
		// TODO: impl
		break;
	}

	if (_playpausecallbackhandler != 0)
		_playpausecallbackhandler(Deck, PlayState[Deck - 1]);
}

void DoCue(byte Deck)
{
	if (_cuecallbackhandler != 0)
		_cuecallbackhandler(Deck);
}

void DoPitchChange(byte Deck, byte Pitch)
{
	float PitchFloat = PitchByteToPercent(Pitch);

	if (_pitchchangecallbackhandler != 0)
		_pitchchangecallbackhandler(Deck, PitchFloat);
}

void DoTimeMode(byte Deck, byte mode)
{
	TimeMode[Deck] = mode;

	if (_timemodecallbackhandler != 0)
		_timemodecallbackhandler(Deck, mode);
}

void DoSearch(byte Deck, byte Speed)
{
	if (Speed == 0)
		return;

	byte Direction = 1; // 1=forward,2=backward

	if (Speed <= 0x10)
	{
		Direction = 1;

		if (Speed == 1)
			Speed = 1;
		else
			Speed = Speed - 0x04;
	}
	else
	{
		Direction = 2;

		if (Speed == 0xff)
			Speed = 1;
		else
			Speed = 0xFC - Speed;
	}

	if (_searchcallbackhandler != 0)
		_searchcallbackhandler(Deck, Direction, Speed);
}

void DoScan(byte Deck, byte Speed)
{
	if (Speed == 0)
		return;

	byte Direction = 1; // 1=forward,2=backward

	if (Speed <= 0x06)
	{
		Direction = 1;
		Speed = Speed - 0x01;
	}
	else
	{
		Direction = 2;
		Speed = 0xFF - Speed;
	}

	if (_scancallbackhandler != 0)
		_scancallbackhandler(Deck, Direction, Speed);
}

void DoOpenClose(byte Deck)
{
	if (_openclosecallbackhandler != 0)
		_openclosecallbackhandler(Deck);
}

void DoTrackChange(byte Deck, byte To)
{
	if (_trackchangecallbackhandler != 0)
		_trackchangecallbackhandler(Deck, To);
}

void DoIndexChange(byte Deck, byte To, byte Direction)
{
	if (_indexchangecallbackhandler != 0)
		_indexchangecallbackhandler(Deck, To, Direction);
}

void DoReverse(byte Deck)
{
	if (_reversecallbackhandler != 0)
		_reversecallbackhandler(Deck);
}

void DoKeyChange(byte Deck, byte Mode, byte IsNegative, byte Key)
{
	if (_keychangecallbackhandler != 0)
		_keychangecallbackhandler(Deck, Mode, KeyByteToFloat(IsNegative, Key));
}
