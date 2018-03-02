/*******************************************************************************
 * Names: Kevin Chau / Brian Thai
 * Filename: HCNode.cpp
 * Description: File for manipulation of HCNode objects, contains one
 *              method: less-than operator for comparing HCNodes
 * Accounts: cs100sai / brthai
 * PID: A99039092 / A11990995
*******************************************************************************/

#include "HCNode.hpp"
#include "HCTree.hpp"
#include <iostream>
#define ONES 255
#define SHIFTONE 8
#define SHIFTTWO 16

using namespace std;

/** 
 * Less than operator for comparing HCNodes; count takes precedence over symbol
 */
bool HCNode::operator<(const HCNode& other) {

    // if counts are equal, compare symbols. otherwise, compare counts
    if(count == other.count) return (symbol < other.symbol);

    else return (count < other.count);
}
