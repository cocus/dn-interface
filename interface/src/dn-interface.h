#ifndef _DN_INTERFACE_H
#define _DN_INTERFACE_H

#include <stdbool.h>

typedef unsigned char byte;

/* Supported models */
#define MODEL_DN2000F_MK_II 0
#define MODEL_DN2500F 1

/* Callback signatures */
typedef void(*PitchChangeCallback)(byte Deck, float PitchPercent);
typedef void(*TimeModeCallback)(byte Deck, byte Mode);
typedef void(*PlayPauseCallback)(byte Deck, bool IsPlaying);
typedef void(*CueCallback)(byte Deck);
typedef void(*SearchCallback)(byte Deck, byte Direction, byte Speed);
typedef void(*ScanCallback)(byte Deck, byte Direction, byte Speed);

/* Exported functions to register callbacks */
_declspec(dllexport) void SetPitchChangeCallback(PitchChangeCallback handler);
_declspec(dllexport) void SetTimeModeCallback(TimeModeCallback handler);
_declspec(dllexport) void SetPlayPauseCallback(PlayPauseCallback handler);
_declspec(dllexport) void SetCueCallback(CueCallback handler);
_declspec(dllexport) void SetSearchCallback(SearchCallback handler);
_declspec(dllexport) void SetScanCallback(SearchCallback handler);

/* Exported functions to update the driver */
_declspec(dllexport) int Init(char *ComPort, byte Model);
_declspec(dllexport) void Load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);
_declspec(dllexport) void UpdateTime(byte Deck, byte Minute, byte Second, byte Frame);
_declspec(dllexport) void UpdateTimeMode(byte Deck, byte Mode);
_declspec(dllexport) void Cue(byte Deck, byte Minute, byte Second, byte Frame);

#endif /* !_DN_INTERFACE_H */