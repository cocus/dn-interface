using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PlayerDemo
{
    static class Native
    {
//        private const string DLL_NAME = "dn-interface.dll";
        private const string DLL_NAME = @"C:\Users\cocus\Downloads\denon-dn-interface-code-r15-trunk\vs\x64\Debug\dn-interface.dll";

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void PitchChangeCallback(byte Deck, float Pitch);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void TimeModeCallback(byte Deck, byte Mode);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void PlayPauseCallback(byte Deck, bool IsPlaying, bool EnableBreak);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void CueCallback(byte Deck);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SearchCallback(byte Deck, byte Direction, byte Speed);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ScanCallback(byte Deck, byte Direction, byte Speed);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void OpenCloseCallback(byte Deck);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void TrackChangeCallback(byte Deck, byte To);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void IndexChangeCallback(byte Deck, byte To, byte Direction);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ReverseCallback(byte Deck);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void PlayModeChangeCallback(byte Deck, byte Mode);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void VoiceReducerChangeCallback(byte Deck, bool Enabled);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void KeyChangeCallback(byte Deck, byte Mode, float Key);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int Init(string ComPort, byte Model);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int DeInit();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPitchChangeCallback(PitchChangeCallback handler);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTimeModeCallback(TimeModeCallback handler);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPlayPauseCallback(PlayPauseCallback handler);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetCueCallback(CueCallback handler);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetSearchCallback(SearchCallback handler);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetScanCallback(ScanCallback handler);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetOpenCloseCallback(OpenCloseCallback handler);
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTrackChangeCallback(TrackChangeCallback handler);
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetIndexChangeCallback(IndexChangeCallback handler);
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetReverseCallback(ReverseCallback handler);
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPlayModeChangeCallback(PlayModeChangeCallback handler);
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVoiceReducerChangeCallback(VoiceReducerChangeCallback handler);
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetKeyChangeCallback(KeyChangeCallback handler);


        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int UpdateTime(byte Deck, byte Minute, byte Second, byte Frame);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Cue(byte Deck, byte Minute, byte Second, byte Frame);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int UpdateTimeMode(byte Deck, byte Mode);



        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Play(byte Deck);
        
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Pause(byte Deck);
    }
}
