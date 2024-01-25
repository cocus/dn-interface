/*
* Comms to the Denon remote.
*
* Windows.
*
* Copyright 2010-2018 Pete Jefferson <pete.jefferson@gmail.com>
*
*/

#include <Windows.h>
#include <stdbool.h>
#include "..\comms.h"

#define LOG

/* The serial port handle */
HANDLE _comport = 0;

/* For async ops */
OVERLAPPED _read_overlapped = { 0 };
OVERLAPPED _write_overlapped = { 0 };

int _packet_size = 0;

DWORD WINAPI read_from_remote(LPVOID lpParam);

comms_packet_receive_func _comms_packet_receive = 0;

void comms_set_packet_receive_func(comms_packet_receive_func func)
{
	_comms_packet_receive = func;
}

int comms_init(const char *port, int baud, int packetsize, comms_packet_receive_func func)
{
	_packet_size = packetsize;
	_comms_packet_receive = func;

	_comport = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

	/* Configure the serial port */
	DCB dcb;
	SecureZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	if (!GetCommState(_comport, &dcb))
		return ERR_COMPORT_INIT_GET_STATE;

	dcb.BaudRate = baud;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;

	if (!SetCommState(_comport, &dcb))
		return ERR_COMPORT_INIT_SET_STATE;

	/* Initialise overlapped for async read/write */
	_read_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	_write_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	/* Create the read thread */
	DWORD tid = 0;
	bool readthread = CreateThread(NULL, 0, read_from_remote, NULL, 0, &tid);

	if (!readthread)
		return ERR_COMPORT_INIT_READ_THREAD;

	return ERR_OK;
}

/* Sends a packet */
bool comms_send(packet *p)
{
	DWORD written = 0;
	bool res = WriteFile(_comport, p, _packet_size, &written, &_write_overlapped);
	WaitForSingleObject(_write_overlapped.hEvent, INFINITE);
	GetOverlappedResult(_comport, &_write_overlapped, &written, FALSE);
	return true;
}

/* Read loop thread */
DWORD WINAPI read_from_remote(LPVOID lpParam)
{
	/* Read buffer */
	ppacket packet = (ppacket)malloc(_packet_size);
	
	/* Loop forever */
	for (;;)
	{
		byte Offset = 0;
		DWORD TotalRead = 0;

		/* Forever, until we get a full packet */
		for (;;)
		{
			DWORD read = 0;
			bool res3 = ReadFile(_comport, packet + Offset, _packet_size - TotalRead, &read, &_read_overlapped);

			WaitForSingleObject(_read_overlapped.hEvent, INFINITE);

			/* Wait for the read to finish */
			GetOverlappedResult(_comport, &_read_overlapped, &read, FALSE);
			
			/* Move the buffer along */
			Offset = Offset + read;
			TotalRead = TotalRead + read;

			/* Process the packet if it's complete */
			if (TotalRead == _packet_size)
			{
				_comms_packet_receive(packet);

				/* Next packet. Reset the buffer */
				Offset = 0;
				break;
			}
		}
	}
}