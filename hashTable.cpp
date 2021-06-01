#include <iostream>
#include <string>
#include "hashTable.h"
#include <list>

using namespace std;

//Basic constructor
hashTable::hashTable() {
  this->BUCKET = 7;
  table = new list<string>[BUCKET];
}

//Hash table of size P
hashTable::hashTable(unsigned int P) {  // Construct a hash table of size P
  this->BUCKET = P;
  table = new list<string>[BUCKET];
}

//Destructor
hashTable::~hashTable() {
}
  
//insert() function works as STL version
void hashTable::insert(string key) {
  int hash = hashFunction(key);
  string prefix;
  int phash;
  for (int i = 1; i <= key.length(); i++) {
    prefix = key.substr(0, i);
    phash = hashFunction(prefix);
    table[phash].push_back("p " + prefix);
  }
  table[hash].push_back(key);
}

//A function to find words by prefix to reduce average runtime
bool hashTable::prefix(string key){
  int hash = hashFunction(key);
  bool found = false;
  list<string>::iterator i;
  for (i = table[hash].begin(); i != table[hash].end(); i++) { 
    if (*i == "p " + key) {
      found = true;
    }
  }
  return found;
}

//contains() function works as STL version
bool hashTable::contains(string key) {
  int hash = hashFunction(key);
  bool found = false;
  list<string>::iterator i;
  for (i = table[hash].begin(); i != table[hash].end(); i++) { 
    if (*i == key) {
      found = true;
    }
  }
  return found;

//Basic hash function
}
int hashTable::hashFunction(string key) {
  int hash = 7;
  for (int i = 0; i < key.length(); i++) {
    hash = (hash*31 + key[i]) % BUCKET;
  }
  return hash;
}
