#ifndef _GLOBAL_H
#define _GLOBAL_H

/*
* This file contains global error codes and types.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#define ERR_OK 0
#define ERR_PACKET_ALLOCATION 1
#define ERR_PACKET_SEND 2
#define ERR_INVALID_DECK 3
#define ERR_NOT_LOADED 4

#define ERR_BUFFER_INIT_SEM 100
#define ERR_BUFFER_INIT_CRIT 101
#define ERR_BUFFER_INIT_NODE_ALLOC 102
#define ERR_BUFFER_INIT_PACKET_ALLOC 103
#define ERR_BUFFER_ALLOC_TIMEOUT 110
#define ERR_BUFFER_ALLOC_CRIT_TIMEOUT 111
#define ERR_BUFFER_RELEASE_SEM 112
#define ERR_BUFFER_NULL 113

#define ERR_COMPORT_INIT_DCB 200
#define ERR_COMPORT_INIT_GET_STATE 201
#define ERR_COMPORT_INIT_SET_STATE 202
#define ERR_COMPORT_INIT_READ_THREAD 203

#define ERR_MODEL_UNSUPPORTED 300;

enum dn_pitch_range
{
	Four,
	Eight,
	Sixteen
};

#endif /* !_GLOBAL_H */