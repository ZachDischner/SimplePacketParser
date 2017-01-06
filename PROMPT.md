Serial Message Parser
+++++++++++++++++++++

For this exercise, you will implement a parser that breaks a serial stream into packets, while discarding malformed data sequences. The message format and requirements for the program are described below.

Code should be written in C and compile on GCC 4.9. Please include build instructions.

Several sample files are included.

Requirements
============

* The program should read from stdin and write to stdout in the formats described below
* Status or debugging messages may be reported on stderr. There are no restrictions on the format of the status/debug messages.
* Messages consist of a header and a /variable/ length payload. Any data that does not conform to the message format should be discarded.
* The payload is an array of bytes, and may contain any 8-bit byte (0-255). No escaping is performed.
* The program should terminate cleanly when EOF is reached.
* The program should handle inputs of (reasonably) large size.

Message Format
===============

Offset  Value    Type     Meaning

0       0x21     (byte)   start marker 0
1       0x22     (byte)   start marker 1
2       (length) (uint8)  length of payload
3-258   (array)  (bytes)  payload

Output format
=============

Report the length of each packet's payload as an integer enclosed in curly braces (right justified), and report the packet payload as series of hexadecimal numbers corresponding to each byte and separated by spaces. Separate each packet with a newline. An example of the expected output is show below:

{  3} 41 42 43
{  4} 64 65 66 67

Note that the only acceptable characters in the output stream are " 012345689{}ABCDEF" and newline ("\n").

The contents of packet headers and any invalid data should not be reported. Incomplete packets should not be reported.

Example files
==============

README               this file.
2_packets            2 packets
10_short_packets     10 packets of small size
10_short_packets.out parsed output of 10_short_packets
200_packets          A larger sample file
extra_data           Another large sample file with extra data inserted between (valid) packets
