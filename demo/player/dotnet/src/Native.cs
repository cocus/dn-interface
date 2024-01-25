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
        public delegate void PlayPauseCallback(byte Deck);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void CueCallback(byte Deck);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SearchCallback(byte Deck, byte Direction, byte Speed);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ScanCallback(byte Deck, byte Direction, byte Speed);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int Init(string ComPort, byte Model);

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
        public static extern void Load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void UpdateTime(byte Deck, byte Minute, byte Second, byte Frame);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Cue(byte Deck, byte Minute, byte Second, byte Frame);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void UpdateTimeMode(byte Deck, byte Mode);
    }
}
