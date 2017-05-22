
#include "Dictionary.h"

Dictionary::Dictionary(){
	nextCode = 256;

	resetDict();

}

int Dictionary::getNextCode(){
	int code = nextCode;
	++nextCode;
	if (nextCode==4096){
		nextCode=256;
		resetDict();
		return code;
	}
	return code;
}

void Dictionary::addEntry(std::string entry, int atIndex) {
	dict[atIndex] = entry;
}

std::string Dictionary::lookup(int code) {
	return dict[code];
}

bool Dictionary::hasEntry(int code){
	if (dict[code]=="") return false;
	else return true;
}

void Dictionary::resetDict(){
	for (int i=0; i<256; ++i){
		dict[i] = (char) i;
	}
	for (int i=256; i<4096; ++i){
		dict[i] = "";
	}

}
