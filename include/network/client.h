/*
*
*   include/network/client.h   
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

#ifndef NETWORK_CLIENT_FUNCTIONS_H
#define NETWORK_CLIENT_FUNCTIONS_H

/* Prevent include/network/server.h from being included */
#define NETWORK_SERVER_FUNCTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "include/network/network.h"
#include "include/crypt/AES.h"

extern uint32_t AES_KEY[32];
extern socket_t ServerSocket;
extern AES_Counter_t ServerCounter;

/* Unique ID that the server will register to keep track of all the files of the image */
extern int32_t id;

/*  Initate connection with server
*   @param *ip IP address to connect to, ascii or utf-8 null terminated string
*   @param IPv4 IPv4 or IPv6 
*   @return Any error codes that may arise
*/
int connectionInit(char *ip, bool IPv4);

/*  Kill the connection to the server
*   @return Any error codes that may arise
*/
int connectionFini();

/*  Retrieve unique ID from the server, and set it
*   @return Any error codes that may arise
*/
int getID();

/*  Send a file to the server
*   @param *file File to send to the server
*   @param desig Packet designator
*   @return Any error codes that may arise
*/
int sendFile(FILE *file, Packet_Desig_t desig);

/*  Send size bytes at addr to the server
*   @param size Bytes to send
*   @param addr Address to retrieve these bytes from
*   @param desig Packet designator
*   @return Any error codes that may arise
*/
int sendBytes(size_t size, void *addr, Packet_Desig_t desig);

/*  Recieve a packet of max size bytes at addr, blocking.
*   @param size Size to truncate the packet to
*   @param addr Address of the buffer to place the packet
*   @return Any error codes that may arise, or the size of the packet.
*/
size_t recvPacket(size_t size, void *addr);

/*  Get the size of the incoming packet, blocking.
*   @return The size of the incoming packet or any error codes that may arise
*/
size_t getPacketSize();

/*  Filter through incoming packets, until one matching the filter is found, then recieve the packet of max size bytes at addr, blocks until a packet matching the filter is found.
*   @param size Size to truncate the packet to
*   @param addr Address of the buffer to place the packet
*   @param desig Designator to use as a filter
*   @param sig Should the sig be filtered
*   @param val Should the val be filtered
*   @return Any error codes that may arise, or the size of the packet.
*/
size_t recvFiltered_b(size_t size, void *addr, Packet_Desig_t desig, bool sig, bool val);

/*  recvPacket(), but if the incoming packet doesn't match the filter, -1 is returned.
*   @param size Size to truncate the packet to
*   @param addr Address of the buffer to place the packet
*   @param desig Designator to use as a filter
*   @param sig Should the sig be filtered
*   @param val Should the val be filtered
*   @return Any error codes that may arise, or the size of the packet.
*/
size_t recvFiltered_n(size_t size, void *addr, Packet_Desig_t desig, bool sig, bool val);

#endif