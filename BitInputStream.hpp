/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: BitInputStream.hpp
 * Description: BitInputStream ctor and method declarations; allows for 
 *              reading of input stream by bits
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP
#include <iostream>

class BitInputStream{
private:
    char buf; //one byte buffer of bits
    int nbits; //number of bits that have been read from buf
    std::istream & in; //the input stream to use

public:

    BitInputStream(std::istream & is) : in(is){
	buf = 0; //clear buffer
	nbits = 0; //TODO initialize bit index
    }

    /** Fill buffer and reset buffer index
     */
    void fill(){

	    buf = in.get(); //fills the buffer
	    nbits = 0;
    }

    /** Read the next bit in the input stream
     */
    int readBit();

};//end of class

#endif
