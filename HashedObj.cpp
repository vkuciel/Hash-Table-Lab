#include "HashedObj.h"

HashedObj::HashedObj():
	key {""} {}
HashedObj::HashedObj(std::string _key):
	key {_key} {}
HashedObj::HashedObj (const HashedObj& other){
	key = other.key;
}
HashedObj::HashedObj (HashedObj&& other){
	key = std::move(other.key);
}

bool HashedObj::operator==(const HashedObj& other) const {
	if (!key.compare(other.key)){
		return true;
	} else {
		return false; 
	}
}

bool HashedObj::operator!=(const HashedObj& other) const {
	return !(*this == other); 
}

