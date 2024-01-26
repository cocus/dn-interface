#ifndef _DN_INTERFACE_H
#define _DN_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

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
typedef void(*OpenCloseCallback)(byte Deck);
typedef void(*TrackChangeCallback)(byte Deck, byte To);
typedef void(*IndexChangeCallback)(byte Deck, byte To, byte Direction);
typedef void(*ReverseCallback)(byte Deck);
typedef void(*KeyChangeCallback)(byte Deck, byte Mode, float Key);

#ifdef DNINTERFACE_EXPORTS
#define EXPORT_DECLSPEC    __declspec(dllexport)
#else
#define EXPORT_DECLSPEC    __declspec(dllimport)
#endif

/* Exported functions to register callbacks */
EXPORT_DECLSPEC void SetPitchChangeCallback(PitchChangeCallback handler);
EXPORT_DECLSPEC void SetTimeModeCallback(TimeModeCallback handler);
EXPORT_DECLSPEC void SetPlayPauseCallback(PlayPauseCallback handler);
EXPORT_DECLSPEC void SetCueCallback(CueCallback handler);
EXPORT_DECLSPEC void SetSearchCallback(SearchCallback handler);
EXPORT_DECLSPEC void SetScanCallback(SearchCallback handler);
EXPORT_DECLSPEC void SetOpenCloseCallback(OpenCloseCallback handler);
EXPORT_DECLSPEC void SetTrackChangeCallback(TrackChangeCallback handler);
EXPORT_DECLSPEC void SetIndexChangeCallback(IndexChangeCallback handler);
EXPORT_DECLSPEC void SetReverseCallback(ReverseCallback handler);
EXPORT_DECLSPEC void SetKeyChangeCallback(KeyChangeCallback handler);

/* Exported functions to update the driver */
EXPORT_DECLSPEC int Init(const char *ComPort, byte Model);
EXPORT_DECLSPEC int Load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);
EXPORT_DECLSPEC int UpdateTime(byte Deck, byte Minute, byte Second, byte Frame);
EXPORT_DECLSPEC int UpdateTimeMode(byte Deck, byte Mode);
EXPORT_DECLSPEC int Cue(byte Deck, byte Minute, byte Second, byte Frame);
EXPORT_DECLSPEC int Play(byte Deck);
EXPORT_DECLSPEC int Pause(byte Deck);

/* TODO: remove, this is just for testing */
EXPORT_DECLSPEC bool SendRaw(byte* p);

#ifdef __cplusplus
}
#endif

#endif /* !_DN_INTERFACE_H */