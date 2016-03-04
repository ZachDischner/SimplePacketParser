//
//  packetParser.c
//  packetParser
//
//  Created by Zach Dischner on 3/3/16.
//

#include "packetParser.h"

// Hello world!
int main()
{
    printf("Hello World %s\n\n", "zach");

    // Create a struct
    Packet packet;
    packet.payloadLength = 0x05;
    packet.payloadData[0] = 0x44;


    printf("packet length %d\n", packet.payloadLength);
    printf("packet 1: %x \n", packet.payloadData[0]);
    return 0;
}

// char ch;
// while(read(STDIN_FILENO, &ch, 1) > 0)
// {
//  //do stuff
// }
