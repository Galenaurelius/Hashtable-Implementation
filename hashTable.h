#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <list>


using namespace std;

class hashTable {

private:
    unsigned int BUCKET;
    list<string> *table; 
public: 
    //Basic constructor
    hashTable();
    //Hash table of size P
    hashTable(unsigned int P);
    //Destructor
    ~hashTable();
    //insert() function works as STL version
    void insert(string key);   
    //contains() function works as STL version
    bool contains(string key);
    //Basic hash function
    int hashFunction(string key); 
    //A function to find words by prefix to reduce average runtime
    bool prefix(string key);
}; 

#endif
