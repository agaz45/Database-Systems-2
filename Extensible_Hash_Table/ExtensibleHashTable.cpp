#include "ExtensibleHashTable.h"
#include "Bucket.h"
#include <iostream>
#include <string>

using namespace std;

//Constructor, generic hash table has block size = 4
ExtensibleHashTable::ExtensibleHashTable(){
  globalDepth = 1;
  buckets = new Bucket*[2];
  bucketSize = 4;
  buckets[0] = new Bucket(bucketSize);
  buckets[1] = new Bucket(bucketSize);
}

// Constructor for bucket's block size = n
ExtensibleHashTable::ExtensibleHashTable(int n){
  globalDepth = 1;
  buckets = new Bucket*[2];
  bucketSize = n;
  buckets[0] = new Bucket(bucketSize);
  buckets[1] = new Bucket(bucketSize);
}

// Returns 2^n
int ExtensibleHashTable::twoSquared(int n) {
  int temp = 1;
  for (int i=0; i<n; i++) {
    temp = temp * 2;
  }
  return temp;
}

// returns true if the value n is found in the bucket
bool ExtensibleHashTable::find(int n) {
  return buckets[n%twoSquared(globalDepth)]->find(n);
}

// Insert value n into appropriate bucket
void ExtensibleHashTable::insert(int n){
  // While the bucket for the current hashglobalDepth) is full
  while (buckets[n%twoSquared(globalDepth)]->isFull()) {
    int prevNumBuckets = twoSquared(globalDepth);

    //Make sure that value can be inserted into the bucket
    if (buckets[n%twoSquared(globalDepth)]->runTimeError(n)) {
      cout << "RUNTIME ERROR" << endl;
      return;
    }
    // doubles buckets if the buckets local depth is = to global depth
    if (buckets[n%twoSquared(globalDepth)]->getLD() >= globalDepth) {
      doubleBuckets();
    }
    // reallocates the buckets for the bucket that got split
    redoBuckets(n, buckets[n%prevNumBuckets]->getLD());
  } 
  // insert the value into appropriate bucket
  buckets[n%twoSquared(buckets[n%globalDepth]->getLD())]->insert(n);
  return;
}

// Doubles the amount of buckets, and sets the new buckets to the existing ones
void ExtensibleHashTable::doubleBuckets() {
  int prevNumBuckets = twoSquared(globalDepth);
  int numBuckets = twoSquared(globalDepth+1);
  
  Bucket** temp = new Bucket*[numBuckets];
  for (int i=0; i< numBuckets; i++) {
    temp[i] = buckets[i%prevNumBuckets];
  }
  delete buckets;
  buckets = temp;
  globalDepth = globalDepth + 1;
  return;
}

// Redo bucket, and remove values that dont belong in bucket when localdepth is increased
void ExtensibleHashTable::redoBuckets(int n, int depth) {
  int prevNumBuckets = twoSquared(depth);
  int *values = new int[bucketSize];

  int numValues = buckets[n%prevNumBuckets]->outputValues(n%prevNumBuckets, values);
  if (numValues>0){
    buckets[prevNumBuckets + (n%prevNumBuckets)] = new Bucket(bucketSize);
    buckets[prevNumBuckets + (n%prevNumBuckets)]->setLD(buckets[n%prevNumBuckets]->getLD());

    for (int i=0; i<numValues; i++) {
      buckets[prevNumBuckets + (n%prevNumBuckets)]->insert(values[i]);
    }
  }
  delete values;
  return;
}

// Returns true if value was found, and removes the instances of n from the bucket
bool ExtensibleHashTable::remove(int n){
  return buckets[n%twoSquared(globalDepth)]->remove(n);
}


// Prints the Extensible Hash Table
void ExtensibleHashTable::print() {
  // temp is used as a placeholder to check if the previous depths bucket is the same as the next depth bucket(so it doesnt print repeats)
  int temp = 1;
  for (int i=0; i<twoSquared(globalDepth); i++) {
    cout << i << ": " << buckets[i] << " --> ";
    if (i == 0) {
      buckets[i]->print();
    } else {
      if (twoSquared(temp+1) <= i) {
        temp = temp + 1;
      }
      if (i < twoSquared(buckets[i]->getLD())) {
        if (buckets[i] != buckets[i%twoSquared(temp)]) {
          buckets[i]->print();
        }
      }
    }
    cout << endl;
  }
  return;
}

// Deconstructor
ExtensibleHashTable::~ExtensibleHashTable(){
  for (int i = 0; i < twoSquared(globalDepth); i++) {
    delete buckets[i];
  }
  delete buckets;
  buckets = nullptr;
}

// Copy Constructor
ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable& other){
  globalDepth = other.globalDepth;
  bucketSize = other.bucketSize;
  
  buckets = new Bucket*[twoSquared(globalDepth)];
  for (int i=0; i< twoSquared(globalDepth); i++) {
    buckets[i] = other.buckets[i];
  }
}

// Assignment Operator
ExtensibleHashTable& ExtensibleHashTable::operator =(const ExtensibleHashTable& a){
  if (this == &a)
    return *this;

  for (int i = 0; i < twoSquared(globalDepth); i++) {
    delete buckets[i];
  }
  delete buckets; 

  globalDepth = a.globalDepth;
  bucketSize = a.globalDepth;
  buckets = new Bucket*[twoSquared(globalDepth)];
  for (int i=0; i< twoSquared(globalDepth); i++) {
    buckets[i] = a.buckets[i];
  }
  return *this;
}
