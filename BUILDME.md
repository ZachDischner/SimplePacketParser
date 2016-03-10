## packetParser.c Build Instructions
Built with gcc on Mac OSX (Apple LLVM version 7.0.2 (clang-700.1.81))
Tested against gcc-4.9, also installed on OSX alongside LLVM clang compiler

I provide a few build methods mainly because I have wanted to try some `make` alternatives for a while. `scons` is fairly well known. `redo` is a new growing option, both work to produce the same output though, and both are overkill for this simple program. Both can be installed on OSX easily enough with `brew install scons` and `brew install redo`. You can always just skip to the Raw Command Line instructions below. 

# Build Using Scons
http://scons.org/
```
scons
```

Clean up with:

```
scons -c
```

# Build Using Redo
http://cr.yp.to/redo.html

```
redo all
```

Clean up with 
```
redo clean
```

# Raw Command Line Compilation Instructions
```
gcc -o packetParser.o -c -Wall -Wextra -g -pedantic -std=iso9899:1999 packetParser.c
gcc -o packetParser packetParser.o
``` 

## Test
Once compiled, run the program from the command line, supplying the packet file to parse as the first and only argument

```
./packetParser 2_packets
```
A python utility to test all packets at once is provided as a quick sanity check. Run with a python 2.7 interpreter:
```
python packetTest.py
```


