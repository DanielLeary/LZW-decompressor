
#include "Decoder.h"

Decoder::Decoder(){
}

void Decoder::decodeFile(std::string fileName){
	std::ifstream inFile (fileName, std::ios::binary);
	std::string outFileName = fileName;
	unsigned sz = outFileName.size();
	outFileName.resize (sz-2);
	outFileName += ".txt";
	std::ofstream outFile (outFileName, std::ios::binary);

	Dictionary dict = Dictionary();
	LZW lzw = LZW();

	if (inFile.is_open()){
		//tells us total bytes we'll be reading so we know when to end
		inFile.seekg(0, inFile.end);
		int totalBytes = inFile.tellg();
		inFile.seekg(0, inFile.beg);

		char * buffer = new char[3];
		char * buffer16 = new char[2];
		int prevCode, currCode;

		//-------------------------------
		// Initial setup for first byte - slightly different to rest of loop
		//-------------------------------
		if(totalBytes>=3) {
			// for normal case of reading 2 codes in 3 bytes
			inFile.read(buffer,3);

			//one time setup of prevCode before loop starts
			std::bitset<12> bits = to12Bit(buffer[0], buffer[1], true);
			prevCode = bit12ToInt(bits);
			outFile << dict.lookup(prevCode);
			//std::cout << dict.lookup(prevCode);

			// Second code processed from rightmost 12 bits
			std::bitset<12> bits2 = to12Bit(buffer[1], buffer[2], false);
			currCode = bit12ToInt(bits2);
			lzw.decode(prevCode, currCode, dict, outFile);

			totalBytes = totalBytes-3;
		}
		else if (totalBytes==2){
			// for end condition, when odd num codes, reading 1 code in 2 bytes
			inFile.read(buffer16,2);

			std::bitset<16> bits = to16Bit(buffer16[0], buffer16[1]);
			prevCode = bit16ToInt(bits);
			outFile << dict.lookup(prevCode);
			//std::cout << dict.lookup(prevCode);

			totalBytes = totalBytes-2;
		}
		else {
			//finish when file has only 1 byte so isn't encoded
			delete[] buffer;
			delete[] buffer16;
			std::cout << "File has no codes\n";
			inFile.close();
			exit(1);
		}


		//-------------------
		// Main Loop - Read 3 bytes at a time from file, and decode them
		//-------------------
		while (inFile || outFile){
			if(totalBytes>=3) {
				// for normal case of reading 2 codes in 3 bytes
				inFile.read(buffer,3);

				// We read 3 bytes at a time so 2 codes - call LZWdecode on both
				std::bitset<12> bits = to12Bit(buffer[0], buffer[1], true);
				currCode = bit12ToInt(bits);
				lzw.decode(prevCode, currCode, dict, outFile);

				// Second code processed from rightmost 12 bits
				std::bitset<12> bits2 = to12Bit(buffer[1], buffer[2], false);
				currCode = bit12ToInt(bits2);
				lzw.decode(prevCode, currCode, dict, outFile);

				totalBytes = totalBytes-3;
			}
			else if (totalBytes==2){
				// for end condition, when odd num codes, reading 1 code in 2 bytes
				inFile.read(buffer16,2);

				std::bitset<16> bits = to16Bit(buffer16[0], buffer16[1]);
				prevCode = bit16ToInt(bits);
				outFile << dict.lookup(prevCode);
				//std::cout << dict.lookup(prevCode);

				totalBytes = totalBytes-2;
			}
			else {
				// finish
				delete[] buffer;
				delete[] buffer16;
				std::cout << "File read successfully\n";
				inFile.close();
				outFile.close();
				exit(1);
			}
		}
	} else {
		std::cout << "Unable to open file\n";
	}
	std::cout << "File read successfully\n";
	inFile.close();
	outFile.close();

}

int Decoder::bit12ToInt(std::bitset<12> bits){
	return (int)(bits.to_ulong());
}
int Decoder::bit8ToInt(std::bitset<8> bits){
	return (int)(bits.to_ulong());
}
int Decoder::bit16ToInt(std::bitset<16> bits){
	return (int)(bits.to_ulong());
}

void Decoder::print12Bit(std::bitset<12> bits){
	std::cout << bit12ToInt(bits) << std::endl;
	std::cout << bits.to_string() << std::endl;
	std::cout << std::endl;
}
void Decoder::print16Bit(std::bitset<16> bits){
	std::cout << bit16ToInt(bits) << std::endl;
	std::cout << bits.to_string() << std::endl;
	std::cout << std::endl;
}



std::bitset<12> Decoder::to12Bit(char byte1, char byte2, bool first12Bits){
	std::bitset<8> b1(byte1);
	std::bitset<8> b2(byte2);
	std::string strBit = b1.to_string() + b2.to_string();

	if(first12Bits){
		strBit.erase(strBit.begin()+13, strBit.end());
	} else {
		strBit.erase(strBit.begin(), strBit.end()-12);
	}

	std::bitset<12> bits(strBit);
	return bits;
}

std::bitset<16> Decoder::to16Bit(char byte1, char byte2){
	std::bitset<8> b1(byte1);
	std::bitset<8> b2(byte2);
	std::bitset<16> bits(b1.to_string() + b2.to_string());
	return bits;
}
