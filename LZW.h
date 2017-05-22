#ifndef LZW_H
#define LZW_H

#include <cstdlib>
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

#include "Dictionary.h"

class LZW {
	public:
		LZW();

		void decode(int &prevCode, int currCode, Dictionary &dict, std::ofstream &outFile);
};



#endif
