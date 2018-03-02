/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: HCTree.cpp
 * Description: Contains methods for creation and manipulation of a Huffman
 *              encoding tree; encoding and decoding methods are defined
 *              here
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/

#include <queue>
#include <vector>
#include <fstream>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <algorithm>

using namespace std;

HCTree::~HCTree() {

    deleteAll(this->root);
}

void HCTree::build(const vector<int>& freqs) {
    
    // create priority queue to store items
    priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> pq;

    // counter for iterating through freqs
    int freqCounter = 0;

    // for each nonzero item in freqs, create node and push to pq
    for(int count : freqs) {

        // if count is nonzero
        if(count) {

            // create node
            HCNode* symNode = new HCNode(count,(byte) freqCounter);

            // set leaves in calling tree to point to nodes
	        this->leaves[freqCounter] = symNode;

    	    //cout << "Leaf:" << *(this->leaves[freqCounter]) << endl;

            // push this node to pq
            pq.push(symNode);
        }

        // increment the freqCounter
        freqCounter++;
    }

    // while there are 2 or more items in the pq
    while(pq.size()>1){

        // store values of two lowest counts
        //Pop the two lowest count trees
        HCNode* s1 = pq.top();
        pq.pop();
        HCNode* s2 = pq.top();
        pq.pop();

        // sum counts and store symbols in new vars
        int totalCount = (s1->count) + (s2->count);
        byte sym1 = s1->symbol;
        byte sym2 = s2->symbol;

        // create new trie with sum of counts
        HCNode* trie = new HCNode(totalCount, sym1);

        if(s1->count != s2->count) {
            trie->symbol = sym1;
            trie->c0 = s1;
            trie->c1 = s2;
        }

        // else if equal
        else{

            // if symbol 1 is less than symbol 2
            if(sym1 < sym2){

                trie->symbol = sym1;
                trie->c0 = s1;
                trie->c1 = s2;
            }//end of if
            
            // otherwise
            else {
            
                trie->symbol = sym2;
                trie->c0 = s2;
                trie->c1 = s1;
            }//end of else

        }//end of else
        
        //Reattach children to trie
        s1->p = trie;
        s2->p = trie;
        
        // push result back into pq
        pq.push(trie);
		
    }//end of while

    // attach root to last item in pq
    this->root = pq.top();

    

}//end of build

void HCTree::encode(byte symbol, ofstream& out) const{

    HCNode* leaf = leaves[(int)symbol];

    //to store the encoding characters (0 or 1)
    vector<int> encoding;

    //while leaf has a parent
    while(leaf->p){
    	if(leaf == leaf->p->c0){
	    encoding.push_back(0);
	    leaf = leaf->p;
	}
	else{
	    encoding.push_back(1);
	    leaf = leaf->p;
    	}
    }//end of while

    reverse(encoding.begin(), encoding.end());
    for(int output : encoding){
    	out << output;

    }//end of for each

}//end of encode

int HCTree::decode(ifstream& in) const {

    // create running HCNode pointer
    HCNode* decoded = root;

    // create variable to store next byte
    int nextByte;

    while(decoded->c0 || decoded->c1) {

        // initialize nextByte to the next byte in the file
        nextByte = in.get() - '0';

        if(nextByte == -1 - '0') return EOF;

        //cout<<nextByte<<".";

        // if EOF, return
        if(nextByte + '0' == 10) {
            return nextByte;
        }

        // if nextByte is 0, go to c0
        if(nextByte == (int) 0) {

            decoded = decoded->c0;
        }

        // if 1, go to c1
        else if(nextByte == (int) 1) {

            decoded = decoded->c1;
        }
    }

    // return the resultant symbol as an int
    return ((int) decoded->symbol);
}

void HCTree::deleteAll(HCNode* n) {

    // if null node, exit
    if(!n) return;

    // recurse left
    if(n->c0) this->deleteAll(n->c0);

    // recurse right
    if(n->c1) this->deleteAll(n->c1);

    // perform deletion
    delete n;
    n = nullptr;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol by calling writeBit.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {

    HCNode* leaf = leaves[symbol];
    vector<int> encoding;

    //while leaf has a parent, get 0 or 1
    while(leaf->p){

    	if(leaf == leaf->p->c0) {

	        encoding.push_back(0);
	        leaf = leaf->p;
	    }

        else {

            encoding.push_back(1);
            leaf = leaf->p;
        }
    }//end of while

    reverse(encoding.begin(), encoding.end());  // encoding is backwards,
                                                // so reverse
    // write all bits of encoding
    for(int output : encoding){
        out.writeBit(output);   
    }

}//end of encode

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */

int HCTree::decode(BitInputStream& in) const {

    HCNode* decoded = root;
    unsigned int bit;

    // decode symbol
    while(decoded->c0 || decoded->c1) {

        // initialize bit to next bit in buf
        bit = in.readBit();
        
        // if 0, traverse c0
        if(bit == 0) decoded = decoded->c0;

        // else (if 1), traverse c1
        else decoded = decoded->c1;
    }

    return (unsigned int)decoded->symbol;
}
