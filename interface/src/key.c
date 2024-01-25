
/*
* Pitch conversion functions.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
* Copyright 2024 Santiago Hormazabal <santiagohssl@gmail.com>
*
*/

#include "dn-interface.h"

const struct
{
	byte input;
	float value;
} key_map[] = {
	{ 167, 16.0 },
	{ 143, 15.0 },
	{ 125, 14.0 },
	{ 111, 13.0 },
	{ 100, 12.0 },
	{ 91, 11.0 },
	{ 83, 10.0 },
	{ 77, 9.0 },
	{ 71, 8.0 },
	{ 65, 7.0 },
	{ 56, 6.0 },
	{ 50, 5.0 },
	{ 40, 4.0 },
	{ 30, 3.0 },
	{ 20, 2.0 },
	{ 10, 1.0 },
	{ 0, 0.0 },
};

/* Convert the packet byte to float */
float KeyByteToFloat(byte IsNegative, byte Pitch)
{
	for (int i = 0; i < 17; i++)
		if (key_map[i].input == Pitch)
			return IsNegative ? -1 * key_map[i].value : key_map[i].value;
	return 0;
}



