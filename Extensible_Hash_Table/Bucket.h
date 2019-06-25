#ifndef BUCKET_H_INCLUDED
#define BUCKET_H_INCLUDED

class Bucket {
public:
	Bucket();
   
	// Construct a new Bucket of size n
	Bucket(int n);
	// Inserts n into the bucket
	void insert(int n);

	//Returns true if bucket is full
	bool isFull();

	//Returns true if there is a runtime error
	bool runTimeError(int n);

	// Returns the local depth of bucket
	int getLD();

	// Sets the Local Depth of bucket, n=-1 is an increase
	void setLD(int n);

	// returns number of values in array
	int outputValues(int n, int *values);

	// Returns true if value is in bucket
	bool find(int n);

	// Returns true if n is in bucket, and removes n from bucket
	bool remove(int n);

	// Prints content of bucket
	void print();

	// Returns amount of entries in bucket
	int size();
   
	// Copy Constructor
	Bucket(const Bucket& other);

	// Destructor
	~Bucket();

	// Copy Assignment Operator
	Bucket& operator = (const Bucket& a);

private:
	int blockSize;
	int entries;
	int* block;
	int localDepth;

	int twoSquared(int n);
};
#endif //BUCKET_H_INCLUDED
