#ifndef _COMMS_H
#define _COMMS_H

#include "global.h"

typedef byte packet;
typedef packet *ppacket;
typedef void(*comms_packet_receive_func)(ppacket p);

int comms_init(const char *port, int baud, int packetsize, comms_packet_receive_func func);

bool comms_send(packet *p);

#endif /* !_COMMS_H */