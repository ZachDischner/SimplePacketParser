/****************************************************************************
 *               Zach Dischner - March 2016                              
 * packetParser.h - packetParser.c                                       
 *                                                                       
 * Parse data file containing 'packets' print content as specified in    
 * README                                                                  
 *                                                                       
 * Assumptions:                                                          
 *      1. 'Packet headers' always describe valid packets.               
 *          -Do not check to see if the actual packet data appears to be 
 *           shorter or longer than the "payload length" specification in
 *           the packet header.                                          
 *          -Do not verify that the file itself contains "payload length"
 *           amounts of data                                             
 *      2. File data in between valid packets is superflous. Ignore and  
 *         just proceed to the next valid packet                         
 ****************************************************************************/

#include "packetParser.h"

int main(int argc, char* argv[])
{
    // Check to make sure that just one file was provided 
    if (argc != 2)
    {
        fprintf(stderr, "Must provide packet a single file to packetParser. Provided %d filenames\n",argc-1);
        exit(EXIT_FAILURE);
    }

    // Argument provided, assume it is the packetfile. Attempt to open.
    char* packet_filename = argv[1];
    FILE* packet_file = loadFileFromArgs(packet_filename);

    /* Read through the file and extract packets
        1. Read file until 0x2122 start indicator is found
        2. Extract packet starting at that location with a function
        3. Print the packet extracted at that location
    */

    uint8_t b1, b2;  /* Two bytes used to store and identify packet starts */
    int cnt = 0;
    fread( &b1, sizeof(b1), 1, packet_file);
    while (!feof(packet_file)) 
    {
        fread( &b2, sizeof(b2), 1, packet_file);
        if ( (b1 == 0x21) & (b2 == 0x22))
        {
            cnt++;
            Packet packet;
            fread( &packet.payload_length, sizeof(packet.payload_length), 1, packet_file);
            fread( &packet.payload_data, packet.payload_length, 1, packet_file);
            print_packet(packet);

    }
        b1 = b2;
    }   
    fprintf(stderr, "Successfully parsed %d packets\n\n",cnt);
    fclose(packet_file);
    exit(EXIT_SUCCESS);
}

/**
 * @brief Attempt to load a file by name
 *
 * Basic function, just takes a filename string and attempts to load the thing. 
 * 
 * @param filename Character array indicating filename relative to executable to load
 * @return theFile FILE pointer http://www.tutorialspoint.com/ansi_c/c_working_with_files.htm
 */
FILE* loadFileFromArgs(char* filename)
{
    FILE* theFile;
    fprintf(stderr, "Attempting to read provided file: '%s'\n", filename);
    if ( (theFile = fopen(filename, "r")) == NULL )
    {
        // Problem occured opening the file. 
        char* errorString = strerror(errno);
        fprintf(stderr, "Error opening file (%s): %s", filename, errorString);
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "File opened succesfully: %s\n", filename);
    return theFile;
}

int print_packet(Packet packet)
{
    printf("{%3d}",packet.payload_length);
    for (int bin = 0; bin < packet.payload_length; bin++)
    {
        printf(" %02X",packet.payload_data[bin]);
    }
    printf("\n");
    return 0;
}
