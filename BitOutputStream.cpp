/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: BitOutputStream.cpp
 * Description: Definition of writeBit from BitOutputStream
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/
#include "BitOutputStream.hpp"
//#include "HCTree.hpp"
//
#define BYTESIZE 8

/** Writes i (which is 0 or 1) to the buffer at the nbits location
 */
void BitOutputStream::writeBit(int i) {

    // if buffer is full, flush
    if(nbits == (int)BYTESIZE) flush();


    buf = (buf << 1) | i;       // fill buffer right to left
    nbits++;
}
