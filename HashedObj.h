#ifndef HASHEDOBJ_H
#define HASHEDOBJ_H

#include <string>

class HashedObj {
public:
	std::string key;  // the key for a hash object 

	HashedObj ();
	explicit HashedObj (const std::string _key);
	explicit HashedObj (const HashedObj& other);
	explicit HashedObj (HashedObj&& other);

	bool operator==(const HashedObj& other) const; // overloading equality check 
	HashedObj& operator=(const HashedObj& other) = default; //overloading copy assignment 
	bool operator!=(const HashedObj& other) const; // overloading inequality check 
}; 



#endif 