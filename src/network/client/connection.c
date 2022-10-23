/*
*
*   src/network/client/connection.c   
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

bool connected = false;
uint32_t AES_KEY[32];
socket_t ServerSocket;
AES_Counter_t ServerCounter;

/*  Initate connection with server
*   @param *ip IP address to connect to, ascii or utf-8 null terminated string
*   @param IPv4 IPv4 or IPv6 
*   @return Any error codes that may arise
*/
int connectionInit(char *ip, bool IPv4)
{
    netLog("connectionInit()", false, NULL);

    if(connected)
    {
        netLog("A call to connectionInit() was mistakenly made, not sure exactly what to do about that, returning.", false, NULL);
        return;
    }

    #ifdef _WIN32

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    #endif

    socket_t sock;
    if(IPv4)
    {
        netLog("IPv4 is being used.", false, NULL);
        netLog("Server IP is %s", false, NULL, ip);

        /* Rather nice of Windows and Unix-like systems to agree for once */

        /* Open the socket*/
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        struct sockaddr_in addr;

        /* Set up the addr struct */
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htobe16(TCP_PORT);
        addr.sin_zero[0] = 0;
        addr.sin_zero[1] = 0;
        addr.sin_zero[2] = 0;
        addr.sin_zero[3] = 0;
        addr.sin_zero[4] = 0;
        addr.sin_zero[5] = 0;
        addr.sin_zero[6] = 0;
        addr.sin_zero[7] = 0;

        connect(sock, &addr, sizeof(addr));
        netLog("Socket open and connection made.", false, NULL);
    }
    else
    {
        /* Since my IDE is being dumb we'll do this later. */
    }

    /* Start the Diffie-Hellman exchange */

    /* A small buffer for our packet headers, both outgoing and incoming. */
    Packet_Header_t pheader;
    
    /* Send Diffie-Hellman init message, should recieve the same thing in response. */
    pheader.size = sizeof(Packet_Header_t);
    pheader.designator.sig_val = DIFFIE_HELLMAN_INIT;
    send(sock, &pheader, sizeof(Packet_Header_t), 0);
    netLog("Sent Diffie-Hellman init packet.", true, &pheader);

    /* Recieve message, and check if it's valid. */
    recv(sock, &pheader, sizeof(Packet_Header_t), MSG_TRUNC);
    if(pheader.designator.sig_val != DIFFIE_HELLMAN_INIT)
        netErrLog("Recieved invalid response to Diffie-Hellman init packet.", LIVE_OR_DIE, true, &pheader, NETWORK_DIFFIE_HELLMAN_INIT_FAILURE);
    else
        netLog("Valid Diffie-Hellman init packet recieved.", true, &pheader);

    /* Buffer for the next packet. */
    uint8_t *buf;

    /* Now, for the real Diffie-Hellman shit. */

    /* Create our secret */
    void *exponent = getPtr();
    void *cme = getPtr();

    /* The CME the server generates */
    void *tcme = getPtr();
    genSecret(exponent);

    /* Create the CME (Combined modulo-exponent )*/
    handleSecret(exponent, cme);

    /* It is up to the server to send the first CME */
    recv(sock, &pheader, sizeof(Packet_Header_t), MSG_PEEK | MSG_TRUNC);
    if(pheader.designator.sig_val != DIFFIE_HELLMAN_CME_EXCHANGE)
        netErrLog("Invalid Diffie-Hellman exchange order.", LIVE_OR_DIE, true, &pheader, NETWORK_DIFFIE_HELLMAN_INVALID_EXCHANGE);

    /* Allocate the buffer size */
    buf = malloc(pheader.size);

    /* Get the packet again */
    recv(sock, buf, pheader.size, MSG_TRUNC);

    /* Convert the packet sent CME to a proper binary form. */
    setStr(buf + sizeof(Packet_Header_t), tcme);

    /* Finish getting our CME. */
    char *CMEstr = getStr(cme);

    /* Set new buffer, to send our CME. */
    size_t bufSize = sizeof(Packet_Header_t) + strlen(CMEstr) + 1;
    free(buf);
    buf = calloc(bufSize, 1);
    ((Packet_Header_t*)buf)->designator.sig_val = DIFFIE_HELLMAN_CME_EXCHANGE;
    ((Packet_Header_t*)buf)->size = bufSize;
    strcpy(buf + sizeof(Packet_Header_t), CMEstr);

    /* Send our CME */
    send(sock, buf, bufSize, 0);
    netLog("Sending our own CME.", false, NULL);

    /* Calculate the final result */
    finalCalc(exponent, tcme);
    char *STRfcme = getStr(tcme);

    /* TODO: Add key derivation function */
    SHA256_M(STRfcme, strlen(STRfcme), AES_KEY);
    netLog("AES key derived from the Diffie-Hellman result.", false, NULL);

    /* TODO: Add IV aggreement and counter creation right here */

    /* Send the last packet and free all our memory and fucking book it out of here. */

    /* We send Diffie-Hellman fini, not the server */
    pheader.designator.sig_val = DIFFIE_HELLMAN_FINI;
    pheader.size = sizeof(Packet_Header_t);
    send(sock, &pheader, sizeof(Packet_Header_t), 0);
    recv(sock, &pheader, sizeof(Packet_Header_t), MSG_TRUNC);
    if(pheader.designator.sig_val != DIFFIE_HELLMAN_FINI)
        netErrLog("Invalid response to the Diffie-Hellman fini packet.", LIVE_OR_DIE, true, &pheader.designator, NETWORK_DIFFIE_HELLMAN_INVALID_EXCHANGE);
    
    /* Free our memory */
    free(buf);
    free(tcme);
    free(cme);
    free(exponent);

    /* Set the socket global variable */
    ServerSocket = sock;
    netLog("Set the ServerSocket global variable, sending normal packets is now possible.", false, NULL);

    /* Log and return */
    connected = true;
    netLog("A connection to the server has been succesfully made and configured, returning.", false, NULL);
    return;
}

/*  Kill the connection to the server
*   @return Any error codes that may arise
*/
int connectionFini();