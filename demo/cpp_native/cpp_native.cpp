// cpp_native.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>


#include <dn-interface.h>


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

    std::cout << "Press any key to load" << std::endl;
    getc(stdin);

    std::cout << "Load() ";
    Load(2, 78, 32, 07);
    std::cout << std::endl;

    std::cout << "Press any key to UpdateTime" << std::endl;
    getc(stdin);
    std::cout << "UpdateTime() ";
    UpdateTime(2, 8, 19, 12);
    std::cout << std::endl;


    std::cout << "Press any key to switch to playing" << std::endl;
    getc(stdin);
    std::cout << "UpdateTime() ";
    Play(2);
    UpdateTime(2, 8, 19, 12);
    std::cout << std::endl;



    std::cout << "Press any key to switch to pause" << std::endl;
    getc(stdin);
    std::cout << "UpdateTime() ";
    Pause(2);
    //UpdateTime(2, 8, 19, 12);
    std::cout << std::endl;

    std::cout << "Press any key to switch to cue" << std::endl;
    getc(stdin);
    std::cout << "UpdateTime() ";
    Cue(2, 80, 80, 55);
    //UpdateTime(2, 8, 19, 12);
    std::cout << std::endl;


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
