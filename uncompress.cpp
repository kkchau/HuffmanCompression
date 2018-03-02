/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: uncompress.cpp
 * Description: Decompression function: builds a Huffman tree based on the 
 *              formatted header of a compressed file, then uses that tree to
 *              analyze and decode the compressed file
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/

#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <fstream>
#include <iostream>

#define ASCII 256
#define NEWLINE 10
#define ZERO 0
#define SHIFTONE 8
#define SHIFTTWO 16

using namespace std;

int main(int argc, char* argv[]) {

    // check number of arguments
    if(argc != 3) {
        //cout << "Invalid number of arguments!\n" 
        //     << "Usage: ./compress <original> <compressed>\n";
        return -1;
    }

    // open input file
    ifstream readFile;
    readFile.open(argv[1], ios::binary);
    BitInputStream bitis(readFile);

    // check file status
    if(!readFile.is_open()) {
        //cout << "Invalid input file! Exiting...\n";
        return -1;
    }

    // seek back to beginning of file
    readFile.seekg(0, ios_base::beg);

    vector<int> freq = vector<int>(ASCII, 0);   // vector of frequencies

    unsigned int nextByte;

    // count frequencies based on formatted header in infile
    for(int freqCounter = 0; freqCounter < ASCII; freqCounter++) {

        // frequencies are 3 bytes in size
        byte left = readFile.get();
        byte mid = readFile.get();
        byte right = readFile.get();

        // assemble frequency count
        nextByte = (right | (mid<<SHIFTONE) | (left<<SHIFTTWO));
        freq[freqCounter] = nextByte;
    }

    // total number of symbols to be decoded
    int symCount = 0;
    for(int s : freq) symCount += s;

    // create and build trie if there were any unique symbols
    HCTree* trie = new HCTree();
    if(symCount != 0) trie->build(freq);

    // create and open output file
    ofstream writeFile;
    writeFile.open(argv[2]);

    bitis.fill();   // initial fill of buf

    // perform decoding only for amount of original symbols and write
    for(int sym = 0; sym < symCount; sym++) {

        writeFile.put((unsigned char) (nextByte = trie->decode(bitis)));
    }

    // close input file
    if(readFile.is_open()) {
        readFile.close();
    }

    // close output file
    if(writeFile.is_open()) {
        writeFile.close();
    }

    // delete tree
    delete trie;
    trie = 0;
}
