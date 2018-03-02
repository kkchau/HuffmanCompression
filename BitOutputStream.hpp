/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: BitOutputStream.hpp
 * Description: BitOutputStream ctor and method declarations; allows for writing
 *              to outstream by bits
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>
//#include "HCTree.hpp"

class BitOutputStream{
private:
    char buf; //one byte buffer of bits
    int nbits; //number of bits that have been written to buf
    std::ostream & out; //reference to the output stream to use

public:
    BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0){
	//clear buffer and bit counter
    }

    void flush(bool forced = false){

        // if this is a forced flush, push bits appropriate spaces to the
        // left before flushing
        if(forced) buf = buf<<(8-nbits);

	    out.put(buf);
	    out.flush();
	    buf = nbits = 0;
    }

    void writeBit(int i);

};//end of class

#endif 
