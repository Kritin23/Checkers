#include "Settings.h"
#include "BoardImage.h"

Settings initTh1(int p1)
{
	Settings th1;
	th1.location = "res\\th 1\\";
	boardImg bi;
	th1.BrdImg.clrDark = { 0,0,0 };
	th1.BrdImg.clrLight = { 255,255,255 };
	th1.BrdImg.clrBckg = { 255,0,0 };
	th1.player1 = p1;
	return th1;
}