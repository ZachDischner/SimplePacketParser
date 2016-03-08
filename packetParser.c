//
//  packetParser.c
//  packetParser
//
//  Created by Zach Dischner on 3/3/16.
//

#include "packetParser.h"

int main(int argc, char* argv[])
{
    // Check to make sure file was provided and that it is openable
    if (argc != 2)
    {
        fprintf(stderr, "Must provide packet a single file to packetParser. Provided %d arguments\n",argc-1);
        exit(EXIT_FAILURE);
    }

    // Argument provided, assume it is the packetfile. Attempt to open.
    packet_filename = argv[1];
    FILE *packet_file;
    fprintf(stderr, "Attempting to read provided Packet File: '%s'\n", packet_filename);
    if ( (packet_file = fopen(packet_filename, "r")) == NULL )
    {
        // Problem occured opening the file. 
        char* errorString = strerror(errno);
        fprintf(stderr, "Error opening file (%s): %s", packet_filename, errorString);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "File opened succesfully: %s\n", packet_filename);

    /* Read through the file and extract packets
        1. Read file until 0x2122 start indicator is found
        2. Extract packet starting at that location with a function
        3. Print the packet extracted at that location
    */

    uint8_t start1, start2;
    size_t newLen;
    int cnt=0;
    fread( &start1, sizeof(start1), 1, packet_file);
    while (!feof(packet_file)) 
    {
        fread( &start2, sizeof(start2), 1, packet_file);

        if ( (start1 == 0x21) & (start2 == 0x22))
        {
            printf("\n\tNew Packet!\n");
            cnt++;
        }

        // printf("*packet_start: %02x%02x\n",packet_start[0], packet_start[1]);
        // printf("NewLen: %d\n", newLen);
        // printf("packet size: %d\n", sizeof(packet_start));
        // if (cnt > 10)
        //     {break;}

        // printf("Packet found! Location %d",newLen);
        start1 = start2;
    }   
    printf("found %d packets\n\n",cnt);
    


    // Create a struct
    Packet packet;
    packet.payload_length = 0x05;
    packet.payload_data[0] = 0x44;


    // printf("packet length %d\n", packet.payload_length);
    // printf("packet 1: %x \n", packet.payload_data[0]);
    fclose(packet_file);
    exit(EXIT_SUCCESS);
}

// char ch;
// while(read(STDIN_FILENO, &ch, 1) > 0)
// {
//  //do stuff
// }
