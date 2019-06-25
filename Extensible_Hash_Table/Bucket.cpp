#include "Bucket.h"
#include <iostream>
#include <string>

using namespace std;

//Empty Constructor
Bucket::Bucket() {
  entries = 0;
  localDepth = 1;
}

//Constructor with bucket size n
Bucket::Bucket(int n) {
  entries = 0;
  localDepth = 1;
  blockSize = n;
  block = new int[n];
}

// Returns the value of 2^n
int Bucket::twoSquared(int n) {
  int temp = 1;
  for (int i=0; i<n; i++) {
    temp = temp * 2;
  }
  return temp;
}

// Inserts n into the block
void Bucket::insert(int n) {
  block[entries] = n;
  entries = entries + 1;
  return;
}

// Returns true if the block is full
bool Bucket::isFull() {
  return (entries == blockSize);
}

// Checks to make sure there is no run time Error (ie. bucket full with same value and adding 1 more)
bool Bucket::runTimeError(int n) {
  if (isFull()) {
    for(int i=0; i<(blockSize-1); i++) {
      if (block[i] != block[i+1]) {
        return false;
      }
    }
    if (block[0] != n){
      return false;
    }
    return true;
  }
  return false;
}

//Returns the local depth of the bucket
int Bucket::getLD() {
  return localDepth;
}

void Bucket::setLD(int n) {
  if (n == -1) {
    localDepth = localDepth + 1;
  } else {
    localDepth = n;
  }
  return;
}

// Returns the number of values returned in the array
int Bucket::outputValues(int n, int* values){
  int num = 0;
  int temp = 0;
  localDepth = localDepth + 1;

  // For all entries check if value stays in bucket
  for (int i=0; i<entries; i++) {
    if (block[i]%twoSquared(localDepth) != n) {
      values[num] = block[i];
      num = num + 1;
    } else {
      block[temp] = block[i];
      temp = temp + 1;
    }
  }
  entries = entries - num; 
  return num;
}

// Returns true if n is in the bucket
bool Bucket::find(int n) {
  for (int i=0; (i<blockSize) && (i<entries);i++) {
    if (block[i] == n){
      return true;
    }
  }
  return false;
}

// Returns true if value is in n and removes n from bucket (handles duplicates)
bool Bucket::remove(int n) {
  int temp = 0;
  int numRemoved = 0;
  for (int i=0; i<entries; i++){
    if (block[i] == n){
      numRemoved = numRemoved + 1;
    } else {
      block[temp] = block[i];
      temp = temp+1;
    }
  }
    entries = entries - numRemoved;
  return numRemoved>0;
}

// Prints content of bucket
void Bucket::print() {
  cout << "[";
  // For each value in the block
  for (int i=0; i<blockSize; i++) {

    //If the next value is in the block
    if (i < entries) {
      cout << block[i];
    } else {
      cout << "-";
    }
    if (i+1<blockSize) {
      cout << ",";
    }
  }
  cout <<"]" << " (" << localDepth << ")";
  return;
}

// Returns amount of entries in bucket
int Bucket::size() {
  return entries;
}

// Deconstructor
Bucket::~Bucket() {
  delete block;
  block = nullptr;
}

// Copy Constructor
Bucket::Bucket(const Bucket& other) {
  blockSize = other.blockSize;
  entries = other.entries;
  block = new int[blockSize];
  for (int i=0; i<blockSize;i++) {
    block[i] = other.block[i];
  }
  localDepth = other.localDepth;
}

// Assignment Operator
Bucket& Bucket::operator =(const Bucket& a) {
  if (this == &a) {
    return *this;
  }
  delete block;
  blockSize = a.blockSize;
  entries = a.entries;
  block = new int[a.blockSize];

  // copy the other blocks values into this one
  for (int i=0;i<blockSize;i++) {
    block[i] = a.block[i];
  }
  localDepth = a.localDepth;
  return *this;
}
