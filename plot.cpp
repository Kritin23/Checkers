#include "plot.h"


plot::plot()
{
	r = 0;
	c = 0;
	color = Null;
	occ = false;
	pcolor = Null;
	pking = false;

}

plot::plot(int8_t col, int8_t row)
{
	this->c = col;
	this->r = row;
	this->color = LIGHT;
	if ((col + row) % 2)	this->color = DARK;
	this->occ = false;
	this->pcolor = false;
	this->pking = false;
}

void plot::piece_in(int8_t pc,bool king)
{
	if (pc == Null)
	{
		this->piece_out();
		return;
	}
	this->occ = true;
	this->pcolor = pc;
	this->pking = king;
}

void plot::piece_out()
{
	this->occ = false;
	this->pcolor = Null;
	this->pking = false;
}