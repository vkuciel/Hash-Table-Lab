#include <cassert> 
#include "HashTable.h" 

HashTable::HashTable(int _size, ResolutionType _resolutionFunction):
	resolutionFunction {_resolutionFunction},
	size {0} 
{
	v = std::vector<HashEntry>{size_t(nextPrime(_size-1))};
} 


// accessors -------------------

// will return the current capacity of the vector storing the HashEntrys 
size_t HashTable::tableCapacity() const {
	return v.capacity(); 
}

// normal hash for strings (we saw in class)
// Takes a HashedObj and will return a hash value. 
// NOTE: this does not ensure it is within range of the 
// tablesize, and therefore your code should ensure it is
// after calling this function. 
int HashTable::hash (const HashedObj& x) const {
	unsigned int hashVal= 0;
	for (int i = 0; i < std::min(3,int(x.key.size())); ++i){
		hashVal = 37*hashVal + x.key[i];
	}

	return hashVal; 
}

// a handy resolution-function selector method. 
// Since we store the resolution type as part of the hash table, 
// we can just call this function in place of 
// linearResolution, quadraticResolution, or doubleHashResolution. 
// Takes: 
// 		i: resolution number (i.e. # of collisions occurred) 
//		x: HashedObj to hash on. Note this is only needed by
//			doubleHashResolution(). 
// Returns:
//		int that is a hash value offset for resolution. 
int HashTable::resolution (int i, const HashedObj& x) const {
	if (resolutionFunction == LINEAR){
		return linearResolution(i);
	} else if (resolutionFunction == QUADRATIC) {
		return quadraticResolution(i);
	} else {
		return doubleHashResolution(i, x);
	}
}

// computes the ith linear resolution offset
int HashTable::linearResolution (int i) const {

	return i;
}

// computes the ith quadratic resolution offset
int HashTable::quadraticResolution (int i) const {

	return i*i;
}

// computes the ith double hash resolution of x
int HashTable::doubleHashResolution (int i, const HashedObj& x) const {

	return i*hash2(x);
}
// second hash function for double hashing. The prime number used can be 
// any prime number that satisfies the criteria (what is the criteria for 
// for second hash function?) 
int HashTable::hash2 (const HashedObj& x) const {

	int num = -1;
	int SLP = size;

	while (num != 0) {
		num = 0;
		SLP--;
		int i = SLP - 1;
		while (i > 1 && num == 0) {
			if ((SLP % num) == 0) {
				num++;
			}
			i--;
		}
	}
	return SLP - (hash(x) % SLP);
}

// takes a HashedObj x and will return a bool; true if x is 
// in the table and false if it is not in the table. 
bool HashTable::contains (const HashedObj& x) const {

	int num = 0;
	int valueOfHash = hash(x);

	while (!(v[(valueOfHash + resolution(num, x)) % size].element == x) && (v[(valueOfHash + resolution(num, x)) % size].info != EMPTY) && (num <= size)) {
		num++;
	}
	valueOfHash = (valueOfHash + resolution(num, x)) % size;
	if (v[valueOfHash].info == ACTIVE && v[valueOfHash].element == x) {
		return true;
	}
	else {
		return false;
	}
}


// prints the private table v.
// Used primarily for testing. 
void HashTable::printAll() const { 
	std::cout << "[ ";
	for (HashEntry a : v){
		std::string blah;
		if (!a.element.key.compare("") || a.info == DELETED){
			blah = "_";
		} else {
			blah = a.element.key;
		}
		std::cout << blah << " ";
	}
	std::cout << "]" << std::endl; 
}

// computes the sieve of eratosthenes and returns the next prime 
// higher than the input x. There are several more efficient ways to 
// find the next prime, see the second answer here:
// http://stackoverflow.com/questions/4475996/given-prime-number-n-compute-the-next-prime
int HashTable::nextPrime (int x) const {

	int a, b, count;
	for (a = x + 1; 1; a++) {
		count = 0;
		for (b = 2; b < a; b++) {
			if (a % b == 0) {
				count++;
				break;
			}
		}
		if (count == 0) {
			return a;
		}
	}
}



// mutators -----------------------------------------------------

// empties the table, and must use /lazy deletion/ 
void HashTable::makeEmpty(){

	int i;
	for (i=0; i<size; i++) {
		v[i].info = EMPTY;
		v[i].element.key = "";
	}
	size = 0;
}


// inserts HashedObj x into the table, if it is not already in table.
// Should call the resolution selector function above. 
bool HashTable::insert(const HashedObj& x){

	int num = 0;
	int valueOfHash = hash(x);

	while (v[(valueOfHash + resolution(num, x)) % size].info == ACTIVE) {
		num++;

	}
	valueOfHash = (valueOfHash + resolution(num, x)) % size;
	v[valueOfHash].element;
	v[valueOfHash].info = ACTIVE;
	size++;

	double loadFactor = (double)size / (double)size;
	if (loadFactor > 0.5) {
		rehash(); // Rehash if the load factor if greater than .5
	}
	return true;
}
bool HashTable::insert(HashedObj&& x){
	HashedObj y {x};
	return insert(y);
}

// removes the specified object if it is active in the table and returns true. 
// If it is not found (i.e. finds an EMPTY position), then it returns false. 
bool HashTable::remove(const HashedObj& x){

	int num = 0;
	int valueOfHash = hash(x);

	while (!(v[(valueOfHash + resolution(num, x)) % size].element == x) && v[(valueOfHash + resolution(num, x)) % size].info != EMPTY && num <= size) {
		num++;
	}
	valueOfHash = (valueOfHash + resolution(num, x)) % size;
	if (num > size || v[valueOfHash].info == EMPTY) {
		return false;
	}
	else {
		v[valueOfHash].info = DELETED;
		v[valueOfHash].element.key = "";
		size--;
		return true;
	}
}

// first computes the load factor for the table. If it is not too large, 
// return from function. Else: 
// finds the next prime after doubling the tablesize, and resizes the table
// v to that size. then it iterates over the old values and rehashes the 
// ACTIVE ones into the new table. 
void HashTable::rehash(){

	int x = 2 * size;
	int iNum = x-1;
	int y = -1;

	while (y != 0) {
		y = 0;
		x++;
		while (y == 0 && iNum > 1) {
			if ((x % iNum) == 0) {
				y++;
			}
			iNum--;
		}
	}

	size = x;
	iNum = 0;
	std::vector<HashEntry> oldTable = v;
	v = std::vector<HashEntry>{size_t(x)};
	for (HashEntry h : oldTable) {
		if (h.info == ACTIVE) {
			insert(h.element);
			h.info = ACTIVE;
			size++;
			           // need to increment # of items
		}
	}
}




