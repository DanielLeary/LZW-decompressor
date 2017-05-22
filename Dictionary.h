#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstdlib>
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

class Dictionary {
	public:
		Dictionary();

		int getNextCode();
		std::string lookup(int code);
		bool hasEntry(int code);
		void addEntry(std::string entry, int atIndex);


	private:
		std::string dict[4096];
		int nextCode;
		void resetDict();
};



#endif
