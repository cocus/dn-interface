#pragma once

/*
* This file contains pitch conversion function prototypes.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#include "global.h"

float PitchByteToPercent(byte Pitch);
byte PitchPercentToByte(float Pitch);
