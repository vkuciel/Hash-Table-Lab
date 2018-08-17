#include <iostream> 
#include <cassert> 
#include <vector> 
#include "HashTable.h"

void testHashedObj(){
	HashedObj a {}; // normal constructor 
	assert(!a.key.compare(""));
	assert(a.key.compare("a"));

	// normal 1-parameter constructor 
	HashedObj b {"hello"};
	assert(!b.key.compare("hello"));

	// testing copy constructor 
	HashedObj c {b};
	assert(!c.key.compare("hello"));

	// testing equality operator 
	assert (c == b);

	// testing move constructor 
	HashedObj d {HashedObj("b")};
	assert(!d.key.compare("b"));

}

void testHashTable(){
	HashTable a {5}; 
	HashedObj b {"asdf"};
	a.insert(b);
	a.insert(HashedObj{"blah"});
	a.insert(HashedObj{"hello"});
	assert (a.contains(HashedObj{"blah"}));
	assert (a.contains(HashedObj{"hello"})); 
	assert (!a.contains(HashedObj{"bye"}));
	// be sure that the table rehashes after inserting 
	// 3 elements into a table of size 5  (load factor over 0.5) 

	a.remove(HashedObj{"blah"});
	assert (!a.contains(HashedObj{"blah"}));


	HashTable c {11,HashTable::QUADRATIC};
	c.insert(HashedObj{"blah"});
	c.insert(HashedObj{"hello"});
	assert (c.contains(HashedObj{"blah"}));
	assert (c.remove(HashedObj{"blah"}) == true);
	assert (c.remove(HashedObj{"bye"}) == false); 
	HashTable d {13,HashTable::DOUBLE}; 
	d.insert(HashedObj{"blah"});
	d.insert(HashedObj{"hello"});
	assert (d.contains(HashedObj{"blah"}));
	assert (d.remove(HashedObj{"blah"}) == true);
	assert (d.remove(HashedObj{"bye"}) == false); 

	assert (a.resolution(5,b) == a.linearResolution(5));
	assert (a.linearResolution(3) == 3);
	assert (a.quadraticResolution(3) == 9);
	assert (a.doubleHashResolution(3,b) == 3*a.hash2(b));
	assert (c.resolution(5,b) == c.quadraticResolution(5));
	assert (d.resolution(5,b) == d.doubleHashResolution(5,b));
}

int main () { 
	testHashedObj();
	//testHashTable();
}


