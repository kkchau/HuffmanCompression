/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: BitInputStream.cpp
 * Description: Definition of readBit from BitInputStream 
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/

#include <iostream>
#include "BitInputStream.hpp"
#define BYTESIZE 8  //sizeof byte

/**
 * Reads the next bit in the buffer until all are read, then refills buffer
 */
int BitInputStream::readBit() {

    unsigned int retval;

    // if buf is completely read (i.e. nbits is at end of buf), read next byte
    if(nbits == (BYTESIZE)) fill();

    // retrieve bit at appropriate location and increment index
    retval = (unsigned int) ((buf >> (BYTESIZE - nbits - 1)) & 1);
    nbits++;

    return retval;
        
}
