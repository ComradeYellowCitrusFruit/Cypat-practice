#ifndef NETWORK_CLIENT_FUNCTIONS_H
#define NETWORK_CLIENT_FUNCTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Port to connect to */
#define TCP_PORT 44252

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
int connectionEnd();

/*  Retrieve unique ID from the server, and set it
*   @return Any error codes that may arise
*/
int getID();

/*  Send a file to the server
*   @param *file File to send to the server
*   @return Any error codes that may arise
*/
int sendFile(FILE *file);

/*  Send size bytes at addr to the server
*   @param size Bytes to send
*   @param addr Address to retrieve these bytes from
*   @return Any error codes that may arise
*/
int sendBytes(size_t size, void *addr);

#endif