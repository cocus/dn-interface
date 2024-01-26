// cpp_native.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>


#include <dn-interface.h>

#include <Windows.h> // for sleep


void PitchChangeHandler(byte Deck, float PitchPercent)
{
    printf("CALLBACK[Deck %d] PitchChangeCallback -> %.2f\n", Deck, PitchPercent);
}
void TimeModeHandler(byte Deck, byte Mode)
{
    printf("CALLBACK[Deck %d] TimeModeCallback -> %s\n", Deck, Mode == 1 ? "Elapsed" : "Remain");
}
void PlayPauseHandler(byte Deck, bool IsPlaying)
{
    printf("CALLBACK[Deck %d] PlayPauseCallback\n", Deck);
}
void CueHandler(byte Deck)
{
    printf("CALLBACK[Deck %d] CueCallback\n", Deck);
}
void SearchHandler(byte Deck, byte Direction, byte Speed)
{
    printf("CALLBACK[Deck %d] SearchCallback -> Direction: %d, Speed: %d\n", Deck, Direction, Speed);
}
void ScanHandler(byte Deck, byte Direction, byte Speed)
{
    printf("CALLBACK[Deck %d] ScanCallback -> Direction: %d, Speed: %d\n", Deck, Direction, Speed);
}


void OpenCloseHandler(byte Deck)
{
    printf("CALLBACK[Deck %d] OpenCloseCallback\n", Deck);
}

void TrackChangeHandler(byte Deck, byte To)
{
    printf("CALLBACK[Deck %d] TrackChangeCallback -> %d\n", Deck, To);
}

void IndexChangeHandler(byte Deck, byte To, byte Direction)
{
    printf("CALLBACK[Deck %d] IndexChangeCallback -> %x (Dir %d)\n", Deck, To, Direction);
}

void ReverseHandler(byte Deck)
{
    printf("CALLBACK[Deck %d] ReverseCallback\n", Deck);
}

void KeyChangeHandler(byte Deck, byte Mode, float Key)
{
    printf("CALLBACK[Deck %d] KeyChangeCallback -> Mode = %d, Value = %.2f\n", Deck, Mode, Key);
}

#if 0

#include "dn2500f.h"

/* Convert to BCD */
byte to_bcd(byte b) {

    byte x = 0;
    byte res = 0;

    while (b > 0)
    {
        res |= (b % 10) << (x++ << 2);
        b /= 10;
    }

    return res;
}

void dn2500f_checksum(dn2500f_packet packet)
{
    //	dn2500f_packet p = packet;
    unsigned short checksum =
        packet[0] + packet[1] + packet[2] + packet[3] + packet[4] + packet[5] +
        packet[6] + packet[7] + packet[8] + packet[9] + packet[10];
    //*p[0] += *p[1] += *p[2] += *p[3] += *p[4] += *p[5] +=
    //*p[6] += *p[7] += *p[8] += *p[9] += *p[10];
    packet[11] = (byte)(checksum >> 8);
    packet[12] = (byte)checksum;
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
    STATUS_STOPPED = 9,
    STATUS_CUED = 4,
    STATUS_PAUSED = 3,
    STATUS_PLAYING = 5,
    STATUS_PAUSED_PLAYING = 6
} DN2500F_PLAYSTATUS;

typedef struct
{
    byte Minute;
    byte Second;
    byte Frame;
} DN2500F_TRIPLE_POS;

struct DN2500_DECK
{
    DN2500F_STATE state;
    /* Var to hold the current time mode for the decks, either PARAM_ELAPSED or PARAM_REMAIN */
    DN2500F_TIMEMODE TimeMode;
    /* Var to hold the current play mode for the decks, either PARAM_SINGLE or PARAM_CONTINUE */
    DN2500F_PLAYMODE PlayMode;
    /* Var to hold the current play state for the decks, either PARAM_PLAYING or PARAM_PAUSED */
    DN2500F_PLAYSTATUS PlayState;
    /* Var to hold the current cue state for the decks. True if the deck is cued else false */
    bool CueState;


    DN2500F_TRIPLE_POS CurrentPosition;
    byte CurrentTrack;

    DN2500F_TRIPLE_POS TotalLength;
    byte TotalTracks;

} decks[2] =
{ {NO_INIT, MODE_REMAIN, MODE_SINGLE, STATUS_STOPPED, false, { 0xff, 0xff, 0xff }, 1, { 0xff, 0xff, 0xff }, 1 },
  {NO_INIT, MODE_REMAIN, MODE_SINGLE, STATUS_STOPPED, false, { 0xff, 0xff, 0xff }, 1, { 0xff, 0xff, 0xff }, 1 } };

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
    /* works on all states */


    decks[Deck].TimeMode = MODE_REMAIN;
    decks[Deck].PlayMode = MODE_SINGLE;
    decks[Deck].PlayState = STATUS_STOPPED;
    decks[Deck].CueState = false;

    decks[Deck].CurrentTrack = 1;
    decks[Deck].CurrentPosition.Minute = 0xff;
    decks[Deck].CurrentPosition.Second = 0xff;
    decks[Deck].CurrentPosition.Frame = 0xff;

    decks[Deck].state = NOT_LOADED;

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
    dn2500f_cmd43(Deck, decks[Deck].PlayState, 0x0); /* not sure */
    Sleep(20);

    /* $02 $44 $09 $01 $01 $FF $FF $FF $00 $00 $01 $03 $4F */
    dn2500f_cmd44(Deck, decks[Deck].PlayState, decks[Deck].TimeMode, decks[Deck].PlayMode, to_bcd(decks[Deck].CurrentTrack), 0xff, 0xff, 0xff);


    return ERR_OK;
}

int dn2500f_load(byte Deck, byte DurationMinutes, byte DurationSeconds, byte DurationFrames)
{
    /* only possible when the deck is not already loaded */
    if (decks[Deck].state != NOT_LOADED)
        return ERR_INVALID_STATE;

    /* switch to PAUSED */
    decks[Deck].PlayState = STATUS_PAUSED;
    decks[Deck].state = LOADING_TRACK;
    decks[Deck].TotalLength.Minute = DurationMinutes;
    decks[Deck].TotalLength.Second = DurationSeconds;
    decks[Deck].TotalLength.Frame = DurationFrames;

    /* turns M (cmd total duration): $02 $42 $01 $12 $78 $32 $07 $0D $2F $00 $00 $01 $44 */
    dn2500f_cmd42(Deck, 0x1, /* num tracks */0x1, decks[Deck].TotalLength.Minute, decks[Deck].TotalLength.Second, decks[Deck].TotalLength.Frame);

    /* CMD43(03, 0): PLAY led OFF, STOP led OFF: $02 $43 $03 $00 $00 $00 $00 $00 $00 $00 $00 $00 $48 */
    dn2500f_cmd43(Deck, decks[Deck].PlayState, 0);

    /* $02 $44 $03 $01 $01 $FF $FF $FF $80 $06 $01 $03 $CF */
    dn2500f_cmd44(Deck, decks[Deck].PlayState, decks[Deck].TimeMode, decks[Deck].PlayMode, to_bcd(decks[Deck].CurrentTrack), 0xff, 0xff, 0xff);

    return ERR_OK;
}

int dn2500f_start_cueing(byte Deck)
{
    if (decks[Deck].state != LOADING_TRACK && decks[Deck].state != PAUSE_WHILE_PLAYING_MODE) // TODO: maybe some other states allow cueing?
        return ERR_INVALID_STATE;


    decks[Deck].PlayState = STATUS_CUED;

    /* CMD43(04, 0): PLAY led OFF, STOP led blinks: $02 $43 $04 $00 $00 $00 $00 $00 $00 $00 $00 $00 $49 */
    dn2500f_cmd43(Deck, decks[Deck].PlayState, 0);
    Sleep(50); // TBD

    if (decks[Deck].state == LOADING_TRACK)
    {
        /* CMD43(04, 1): no changes from before: $02 $43 $04 $01 $00 $00 $00 $00 $00 $00 $00 $00 $4A */
        dn2500f_cmd43(Deck, decks[Deck].PlayState, 1);
        Sleep(50); // TBD
    }
    else
    {
        /* CMD43(04, 0): PLAY led OFF, STOP led blinks: $02 $43 $04 $00 $00 $00 $00 $00 $00 $00 $00 $00 $49 */
        dn2500f_cmd43(Deck, decks[Deck].PlayState, 0);
        Sleep(50); // TBD
    }

    decks[Deck].state = CUEING;

    /* $02 $44 $04 $01 $01 $08 $12 $19 $80 $00 $01 $01 $00 */
    dn2500f_cmd44(Deck, decks[Deck].PlayState,
        decks[Deck].TimeMode,
        decks[Deck].PlayMode,
        to_bcd(decks[Deck].CurrentTrack),
        to_bcd(decks[Deck].CurrentPosition.Minute),
        to_bcd(decks[Deck].CurrentPosition.Second),
        to_bcd(decks[Deck].CurrentPosition.Frame));
    Sleep(50); // TBD

    return ERR_OK;
}

int dn2500f_cue(byte Deck, byte Minute, byte Second, byte Frame)
{
    if (decks[Deck].state != CUEING) // TODO: maybe some other states allow cue?
        return ERR_INVALID_STATE;

    decks[Deck].PlayState = STATUS_CUED;
    decks[Deck].state = CUE_MODE;

    decks[Deck].CurrentPosition.Minute = Minute;
    decks[Deck].CurrentPosition.Second = Second;
    decks[Deck].CurrentPosition.Frame = Frame;


    /* CMD43(04, 1): CMD43(04, 2): PLAY led OFF, STOP led ON (CUE mode): $02 $43 $04 $02 $00 $00 $00 $00 $00 $00 $00 $00 $4B */
    dn2500f_cmd43(Deck, decks[Deck].PlayState, 2);
    Sleep(50); // TBD

    /* $02 $45 $00 $00 $02 $00 $00 $00 $00 $00 $00 $00 $49 */
    dn2500f_cmd45(Deck, 2);
    Sleep(50);
    
    /* $02 $44 $04 $01 $01 $08 $12 $19 $80 $00 $01 $01 $00 */
    dn2500f_cmd44(Deck, decks[Deck].PlayState,
        decks[Deck].TimeMode,
        decks[Deck].PlayMode,
        to_bcd(decks[Deck].CurrentTrack),
        to_bcd(decks[Deck].CurrentPosition.Minute),
        to_bcd(decks[Deck].CurrentPosition.Second),
        to_bcd(decks[Deck].CurrentPosition.Frame));

    return ERR_OK;
}

int dn2500f_play(byte Deck)
{
    if (decks[Deck].state != STATUS_CUED && decks[Deck].state != PAUSE_WHILE_PLAYING_MODE) // TODO: maybe some other states allow play?
        return ERR_INVALID_STATE;

    decks[Deck].PlayState = STATUS_PLAYING;
    decks[Deck].state = PLAY_MODE;

    /* $02 $43 $05 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4A */
    dn2500f_cmd43(Deck, decks[Deck].PlayState, 0);
    Sleep(50); // TBD

    /* $02 $44 $05 $01 $01 $08 $12 $19 $80 $20 $01 $01 $21 */
    dn2500f_cmd44(Deck, decks[Deck].PlayState,
        decks[Deck].TimeMode,
        decks[Deck].PlayMode,
        to_bcd(decks[Deck].CurrentTrack),
        to_bcd(decks[Deck].CurrentPosition.Minute),
        to_bcd(decks[Deck].CurrentPosition.Second),
        to_bcd(decks[Deck].CurrentPosition.Frame));

    return ERR_OK;
}

int dn2500f_pause(byte Deck)
{
    if (decks[Deck].state != STATUS_PLAYING) // TODO: maybe some other states allow pausing?
        return ERR_INVALID_STATE;

    if (decks[Deck].state == STATUS_PLAYING)
    {
        decks[Deck].PlayState = STATUS_PAUSED_PLAYING;
        decks[Deck].state = PAUSE_WHILE_PLAYING_MODE;

        /* $02 $43 $06 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4B */
        dn2500f_cmd43(Deck, decks[Deck].PlayState, 0);
        Sleep(50); // TBD

        /* $02 $44 $06 $01 $01 $08 $06 $10 $00 $00 $01 $00 $6D */
        dn2500f_cmd44(Deck, decks[Deck].PlayState,
            decks[Deck].TimeMode,
            decks[Deck].PlayMode,
            to_bcd(decks[Deck].CurrentTrack),
            to_bcd(decks[Deck].CurrentPosition.Minute),
            to_bcd(decks[Deck].CurrentPosition.Second),
            to_bcd(decks[Deck].CurrentPosition.Frame));

        /* $02 $43 $06 $00 $00 $00 $00 $00 $00 $00 $00 $00 $4B */
        dn2500f_cmd43(Deck, decks[Deck].PlayState, 0);
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


/*int dn2500f_unload(byte Deck);
int dn2500f_update_time(byte Deck, byte Minute, byte Second, byte Frame, bool IsLoaded, bool IsCued, bool IsPaused, bool IsPlaying);
*/
#endif




int main()
{
    std::cout << "Init(): ";
    std::cout << Init("COM7:", MODEL_DN2500F) << std::endl;

    SetPitchChangeCallback(PitchChangeHandler);
    SetTimeModeCallback(TimeModeHandler);
    SetPlayPauseCallback(PlayPauseHandler);
    SetCueCallback(CueHandler);
    SetSearchCallback(SearchHandler);
    SetScanCallback(ScanHandler);
    SetOpenCloseCallback(OpenCloseHandler);
    SetTrackChangeCallback(TrackChangeHandler);
    SetIndexChangeCallback(IndexChangeHandler);
    SetReverseCallback(ReverseHandler);
    SetKeyChangeCallback(KeyChangeHandler);
#if 0
    std::cout << "dn2500f_init_deck(2) = " << dn2500f_init_deck(2) << std::endl;
    std::cout << "Press any key to load" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_load(2, 22, 33, 44) = " << dn2500f_load(2, 22, 33, 44) << std::endl;
    std::cout << "Press any key to start cueing" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_start_cueing(2) = " << dn2500f_start_cueing(2) << std::endl;
    std::cout << "Press any key to cue" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_cue(2, 23, 34, 45) = " << dn2500f_cue(2, 23, 34, 45) << std::endl;
    std::cout << "Press any key to play" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_play(2) = " << dn2500f_play(2) << std::endl;
    std::cout << "Press any key to pause while playing" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_pause(2) = " << dn2500f_pause(2) << std::endl;
    std::cout << "Press any key to start cueing after pause while playing" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_start_cueing(2) = " << dn2500f_start_cueing(2) << std::endl;
    std::cout << "Press any key to cue" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_cue(2, 69, 42, 00) = " << dn2500f_cue(2, 69, 42, 00) << std::endl;
    std::cout << "Press any key to play again" << std::endl;
    getc(stdin);

    std::cout << "dn2500f_play(2) = " << dn2500f_play(2) << std::endl;


    std::cout << "Press any key to exit" << std::endl;
    getc(stdin);




    return 0;
#endif

    
    std::cout << "Press any key to load" << std::endl;
    getc(stdin);

    std::cout << "Load() = " << Load(2, 78, 32, 07) << std::endl;

    std::cout << "Press any key to switch to UpdateTime" << std::endl;
    getc(stdin);
    std::cout << "Cue() = " << UpdateTime(2, 10, 20, 30) << std::endl;;

    std::cout << "Press any key to switch to cue" << std::endl;
    getc(stdin);
    std::cout << "Cue() = " << Cue(2, 80, 80, 55) << std::endl;
    
/*
    std::cout << "Press any key to UpdateTime without play" << std::endl;
    getc(stdin);
    std::cout << "UpdateTime() ";
    UpdateTime(2, 8, 19, 12);
    std::cout << std::endl;*/


    std::cout << "Press any key to switch to playing" << std::endl;
    getc(stdin);
    std::cout << "Play(2) " << Play(2) << std::endl;
    

    int f = 12;
    while (f < 60)
    {
        UpdateTime(2, 8, 19, f);
        f++;
        Sleep(200);
    }


    std::cout << "Press any key to switch to pause" << std::endl;
    getc(stdin);
    std::cout << "Pause(2) = " << Pause(2) << std::endl;



    getc(stdin);

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
