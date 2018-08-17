#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashedObj.h"
#include <iostream> 
#include <vector> 
#include <cmath> 

class HashTable {
public:
	enum EntryType {ACTIVE, EMPTY, DELETED};
	enum ResolutionType {LINEAR, QUADRATIC, DOUBLE};
	
	explicit HashTable(int size = 101, 
		ResolutionType resolution = LINEAR); // init to prime 
	

	// accessors 
	size_t tableCapacity() const; 
	int hash (const HashedObj& x) const; 
	int resolution (int i, const HashedObj& x) const;
	int linearResolution (int i) const; 
	int quadraticResolution (int i) const; 
	int doubleHashResolution (int i, const HashedObj& x) const; 
	int hash2 (const HashedObj& x) const; 
	bool contains (const HashedObj& x) const; 
	void printAll() const; 
	int nextPrime (int x) const; 


	// mutators 
	void makeEmpty();
	bool insert(const HashedObj& x);
	bool insert(HashedObj&& x);
	bool remove(const HashedObj& x);
	void rehash();


private: 
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY) :
			element {e},
			info {i} {}
		HashEntry(HashedObj&& e, EntryType i = EMPTY) :
			element {std::move (e)},
			info {i} {}
	};

	int size; 
	std::vector<HashEntry> v;
	const ResolutionType resolutionFunction;
};



#endif 