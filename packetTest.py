#!/usr/bin/env python

"""
Very quick script to test the execution of compiled 'packetParser' binary 
against sample datasets

Not intended to be a comprehensive validator, just a first step sanity check.

Just run from the command line and verify that everything worked as intended.
"""

###### Imports
import subprocess

###### Variables
test_files       = ["2_packets", "10_short_packets", "200_packets", "extra_data"]
legal_characters = list(" 0123456789{}ABCDEF\n")

###### Functions
def testPacketParser(fname):
    """Call packetParser with fname as an argument

    Function verifies that the call was successful, and that the output is legal 
    and (in the case of 10_short_packets), matches the "truth" value provided

    Args:
        fname: Filename to attempt to process
    
    Returns:
        status: Boolean indicator to tell if processing was successful
    """
    print "Testing packetParser binary on file {}".format(fname)
    print "---------------------------------------------------------------"
    try:
        output = subprocess.check_output(["./packetParser",fname])
        status = True
        if False in [char in legal_characters for char in output.replace("\n","")]:
            print "(ERROR) Illegal characters detected after parsing {}".format(fname)
            status = False
        if fname == "10_short_packets":
            with open("10_short_packets.out",'r') as f:
                truth = "".join(f.readlines())
                if truth != output:
                    print "(ERROR) 10_short_packets parsed without failing, but content does not match truth value"
                    print "Truth\n{0}\nFailed\n{1}\n".format(truth, output)
                    status = False
    except:
        print "Problem parsing file {0}".format(fname)
        status = False
    print "---------------------------------------------------------------\n\n"
    return status 

if __name__ == "__main__":
    ## Test packetParser against all given test files 
    success = {fname:testPacketParser(fname) for fname in test_files}
    print "Success calling 'packetParser' for test files?"
    print "\n".join([" : ".join([str(k),str(v)]) for k,v in success.iteritems()])


