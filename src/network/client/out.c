/*
*
*   src/network/client/out.c   
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
*
*   A collection of programs for cybersecurity competitions and practices
*   Copyright (C) 2022  Alicia Antó Valencía
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <wincrypt.h>
#include <WinSock2.h>

#elif defined(__unix__)

#include <sys/socket.h>

#endif

#include "include/crypt/DH.h"
#include "include/crypt/SHA256.h"
#include "include/network/endian.h"
#include "include/network/network.h"
#include "include/log.h"
#include "include/errors.h"
#include "include/network/client.h"

/*  Send a file to the server
*   @param *file File to send to the server
*   @param desig Packet designator
*   @return Any error codes that may arise
*/
int sendFile(FILE *file, Packet_Desig_t desig)
{
    /* Save the file position */
    fpos_t pos;
    fgetpos(file, &pos);

    if(!connected)
    {
        netErrLog("Attempt to send packet while not connected to the server.", ERROR, false, NULL, NETWORK_PACKET_SEND_ERR);
        return NETWORK_PACKET_SEND_ERR;
    }

    /* Get the file size */
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    /* Allocate some memory for the packet */
    void *packet = malloc(fileSize + sizeof(Packet_Header_t));

    /* Initialize the packet */
    Packet_Header_t header;
    header.designator = desig;
    header.size = fileSize + sizeof(Packet_Header_t);
    *((Packet_Header_t*)packet) = header;
    fread((void*)((uintptr_t)packet + sizeof(Packet_Desig_t)), sizeof(uint8_t), fileSize, file);

    /* Encrypt the packet */
    AES_m(packet, packet, &ServerCounter, fileSize + sizeof(Packet_Desig_t), AES_KEY);

    /* Send the packet */
    send(ServerSocket, packet, fileSize + sizeof(Packet_Desig_t), 0);
    netLog("Sent a packet with a size of %zu to the server.", true, &desig, fileSize + sizeof(Packet_Header_t));

    /* Clean up and return */
    free(packet);
    fsetpos(file, &pos);
    
}

/*  Send size bytes at addr to the server
*   @param size Bytes to send
*   @param addr Address to retrieve these bytes from
*   @param desig Packet designator
*   @return Any error codes that may arise
*/
int sendBytes(size_t size, void *addr, Packet_Desig_t desig);