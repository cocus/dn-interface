/*
* Simple log function.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/


#include "global.h"
#include "log.h"
#include "dn2000fmkii.h"
#include <stdio.h>

void Log(char *Message)
{
	char output[1024];
	sprintf_s(output, 1024, "DRIVER: %s\r\n", Message);
	printf(output);
}
