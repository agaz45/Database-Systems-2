#ifndef EXTENSIBLEHASHTABLE_H_INCLUDED
#define EXTENSIBLEHASHTABLE_H_INCLUDED

#include "Bucket.h"

class ExtensibleHashTable {
public:
	//Construct a new ExtensibleHashTable
	ExtensibleHashTable();

	//Construct a new ExtensibleHashTable with n being the number of keys in each bucket
	ExtensibleHashTable(int n);

	//Returns true or false if n is found in hash table
	bool find(int n);

	//Inserts key into hash table
	void insert(int n);

	//Removes key from hash table(removes duplicates). returns true if found
	bool remove(int n);

	//Prints the contents of the hash table
	void print();

	//Copy Constructor
	ExtensibleHashTable(const ExtensibleHashTable& other);

	//Destructor
	~ExtensibleHashTable();

	//Copy Assignment Operator
	ExtensibleHashTable& operator = (const ExtensibleHashTable& a);

private:
	int globalDepth;
	Bucket** buckets;
	int bucketSize;

        int twoSquared(int n);
	void doubleBuckets();
	void redoBuckets(int n, int depth);
};
#endif //EXTENSIBLEHASHTABLE_H_INCLUDED
