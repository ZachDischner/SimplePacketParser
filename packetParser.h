//
//  packetParser.h
//  packetParser
//
//  Created by Zach Dischner on 3/3/16.
//

#ifndef packetParser_h
#define packetParser_h

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Error tracking variables
extern int errno;

// Functions
int main(int argc, char* argv[]);

// Execution variables
int packet_fd;
char* packet_filename;

// Structure to store a packet of data
typedef struct Packet{
    uint8_t payload_length;
    /* Know maximum size, might as well just define and not worry about 
    malloc and freeing, at cost of memory efficiency */
    uint8_t payload_data[258];
    int packet_valid;   
} Packet;
#endif /* packetParser_h */

