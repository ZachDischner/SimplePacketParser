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

// main function
int main(void);

// Structure to store a packet of data
typedef struct Packet{
    int payloadLength;
    /* Know maximum size, might as well just define and not worry about 
    malloc and freeing, at cost of memory efficiency */
    uint8_t payloadData[258];   
};
#endif /* packetParser_h */

