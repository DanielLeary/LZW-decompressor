#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

#include "Decoder.h"

int bit12ToInt(std::bitset<12> bits);
int bit8ToInt(std::bitset<8> bits);
int bit16ToInt(std::bitset<16> bits);

void print12Bit(std::bitset<12> bits);
void print16Bit(std::bitset<16> bits);


std::bitset<12> to12Bit(char byte1, char byte2, bool first12Bits);
std::bitset<16> to16Bit(char byte1, char byte2);



#endif
