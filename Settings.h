#pragma once

#include <string>
#include "BoardImage.h"
class Settings
{
public: 
	std::string location;
	boardImg BrdImg;
	int player1; //DARK OR LIGHT
};
Settings initTh1(int p1);

