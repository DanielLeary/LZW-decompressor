#include "LZW.h"

LZW::LZW(){

}

void LZW::decode(int &prevCode, int currCode, Dictionary &dict, std::ofstream &outFile){
	char ch;
    std::string entry = dict.lookup(currCode);
	if (entry != ""){
		//std::cout << entry;
		// for normal condition when we have the code in dict
		outFile << entry;
	    char ch = entry.at(0);
		std::string forDict = ((dict.lookup(prevCode))+ch);
		dict.addEntry(forDict, dict.getNextCode());
	} else {
		// for special case where need entry that hasn't been processed yet
		char ch = dict.lookup(prevCode).at(0);
		std::string forDict = ((dict.lookup(prevCode))+ch);
		dict.addEntry(forDict, dict.getNextCode());
		//std::cout << forDict;
		outFile << forDict;
	}
	prevCode = currCode;

}
