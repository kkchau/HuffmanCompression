/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: compress.cpp
 * Description: Compression function: creates a Huffman tree using a frequency
 *              vector built from an input file; outputs encoding into a new 
 *              file as specified by the user
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/

#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <fstream>
#include <iostream>

#define ONES 255
#define SHIFTONE 8
#define SHIFTTWO 16

using namespace std;

int main(int argc, char* argv[]){

    // check number of arguments
    if(argc != 3) {
        //cout << "Invalid number of arguments!\n" 
        //     << "Usage: ./compress <original> <compressed>\n";
        return -1;
    }

    // vector to store frequencies, initialized to 0
    vector<int> freq = vector<int>(256, 0);

    // open input file
    ifstream readFile;
    readFile.open(argv[1], ios::binary);

    // check file status
    if(!readFile.is_open()) {
        //cout << "Invalid input file! Exiting...\n";
        return -1;
    }

    // check empty file
    readFile.seekg(0, ios_base::end);
    unsigned int len = readFile.tellg();
    
    // seek back to beginning of file
    readFile.seekg(0, ios_base::beg);

    unsigned int nextByte;

    // if nonempty file, perform symbol count
    if(len != 0) while((nextByte = readFile.get()) != EOF) freq[nextByte]++;

    //move back to beginning of stream
    readFile.clear();
    readFile.seekg(0, ios_base::beg);
   
    // create and build tree if at least one unique symbol
    HCTree* tree = new HCTree();
    if(len != 0) tree->build(freq);

    // open output file
    ofstream writeFile;
    writeFile.open(argv[2]);
    BitOutputStream bitos(writeFile);


    // write header (frequencies) as sets of 3bytes
    for(int f : freq) {

        // create bytes
        byte right = (f & ONES);
        f >>= SHIFTONE;
        byte mid = (f & ONES);
        f >>= SHIFTONE;
        byte left = (f & ONES);

        // put bytes
        writeFile.put(left);
        writeFile.put(mid);
        writeFile.put(right);
    }

    // perform encoding if at least one unique symbol
    if(len != 0) {

        while((nextByte = readFile.get()) != EOF) {

            if(nextByte == EOF) break;      // break at EOF
            tree->encode(nextByte, bitos);
        }

        // extra flush to write rest of bits
        bitos.flush(true);
    }

    // close input file
    if(readFile.is_open()) {
        readFile.close();
    }

    // close output file
    if(writeFile.is_open()) {
        writeFile.close();
    }

    // delete the tree
    delete tree;
    tree = 0;

}//end of main
