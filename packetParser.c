/****************************************************************************
 *               Zach Dischner - March 2016                              
 * packetParser.h - packetParser.c                                       
 *                                                                       
 * Parse data file containing 'packets' print content as specified in    
 * README                                                                  
 *                                                                       
 * Assumptions:                                                          
 *      1. 'Packet headers' nearly always describe valid packets.               
 *          -Do not check to see if the actual packet data appears to be 
 *           shorter or longer than the "payload length" specification in
 *           the packet header.                                       
 *          -The only place where 'invalid' packets are checked is to verify 
 *           that the file contains at least "payload length" bytes left to
 *           be read.                                             
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
    FILE* packet_file= NULL;
    loadFile(packet_filename, &packet_file);

    /* Read through the file and extract packets
        1. Read file until 0x2122 start indicator is found
        2. Extract packet starting at that location with a function
        3. Print the packet extracted at that location
    */

    uint8_t b1, b2;     // Two bytes used to store and identify packet starts 
    int packetCount = 0;
    Packet packet;      // Packet struct storage container for packet information 
    fread( &b1, sizeof(b1), 1, packet_file);  //read first byte of file
    while (!feof(packet_file)) 
    {
        /* Read next byte from the file.
            See if previous byte (b1) and next byte (b2) == 0x21 and 0x22 respectively
            If so, the next dataset in the file is a packet to be parsed
        */
        fread( &b2, sizeof(b2), 1, packet_file);
        if ( (b1 == 0x21) & (b2 == 0x22))
        {
            // Populate packet stctuc with the payload_length, then the next payload_length number of bytes 
            // fread( &packet.payload_length, sizeof(packet.payload_length), 1, packet_file);
            // fread( &packet.payload_data, packet.payload_length, 1, packet_file);
            // Valid packet starts here. Extract.
            extractPacket(packet_file, &packet);
            if (packet.packet_valid == 1) {packetCount++;}

            // Print out packet 
            printPacket(&packet);

        }
        b1 = b2; /* Second byte becomes the first byte nex time around in [b1,b2] == 0x2122*/
    }   
    fprintf(stderr, "Successfully parsed %d packets\n\n",packetCount);
    fclose(packet_file);
    exit(EXIT_SUCCESS);
}

/**
 * @brief Attempt to load a file by name
 *
 * Basic function, just takes a filename string and attempts to load the thing. If the filenam
 * isn't available or can't be opened, exit the program. 
 * 
 * @param filename Character array indicating filename relative to executable to load
 * @param theFile pointer to FILE pointer. Passed by reference for use in calling function. http://www.tutorialspoint.com/ansi_c/c_working_with_files.htm
 */
void loadFile(char* filename, FILE** theFile)
{
    fprintf(stderr, "Attempting to read provided file: '%s'\n", filename);
    if ( (*theFile = fopen(filename, "r")) == NULL )
    {
        // Problem occured opening the file. 
        char* errorString = strerror(errno);
        fprintf(stderr, "Error opening file (%s): %s", filename, errorString);
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "File opened succesfully: %s\n", filename);
}

/*
 * @brief Extract a packet from a serial data stream
 *
 * Assumes that the stream's read position now points at the start of a packet. Extracts the number
 * of bytes from the stream as specified by the packet header at the beginning of the stream and 
 * populate a Packet data structure with data. Minimal packet content checking marks a packet as 
 * invalid if the packet header suggests that the file is too small to accommodate
 * 
 * @param packet_file FILE steam pointer containing packet data
 * @param packet Pointer to a packet data structure to be filled (returned by reference)
 * @return _ 0/1 success/failure indicator. Failure criteria not yet defined so always returns 0...
 */
int extractPacket(FILE* packet_file, Packet* packet)
{
    // Populate packet stctuc with the payload_length, then the next payload_length number of bytes 
    fread( &packet->payload_length, sizeof(packet->payload_length), 1, packet_file);
    
    /* Verify that there is at least 'payload_length' number of bytes left in the file
        This is the only 'incomplete' packet detection logic implemented
        1. Get current position in file
        2. Seek to the end of the file
        3. Get the difference between the current position and the end of the file (num bytes)
        4. Compare against packet header "payload length". 
        5. Mark packet as invalid if not enough data exists in the file (but still read the data just to close out the file)
    */
    int current_position = ftell(packet_file);
    fseek(packet_file, 0L, SEEK_END);
    int filesize = ftell(packet_file);   
    fseek(packet_file, current_position, SEEK_SET); 
    fread( &packet->payload_data, packet->payload_length, 1, packet_file);
    packet->packet_valid = 1;
    if ((filesize - current_position) < packet->payload_length)
    {
        fprintf(stderr,"Packet specifies %d bytes of packet_data, but only %d bytes remain in file. Marking as invalid\n",packet->payload_length, filesize - current_position );
        packet->packet_valid = 0;
    }
    // No further error checking is performed, packet assumed to be valid
    return 0;
}

/*
 * @brief Prints a packet data structure
 *
 * Takes a packet data structure, print it out according to the README specifications. Do nothing for
 * invalid packets
 * 
 * @param packet Packet data structure to print out
 * @return _ 0/1 success/failure indicator. Failure criteria not yet defined so always returns 0...
 */
int printPacket(Packet* packet)
{
    // Ignore invalid packet
    if (packet->packet_valid == 0)
    {
        return 0;
    }

    // Print out formatted packet data
    // ex: { 3} 11 22 FF
    printf("{%3d}",packet->payload_length);
    for (int bin = 0; bin < packet->payload_length; bin++)
    {
        printf(" %02X",packet->payload_data[bin]);
    }
    printf("\n");
    return 0;
}
