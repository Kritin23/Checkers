#pragma once


typedef signed char int8_t;

class plot
{
public:
	int8_t c;
	int8_t r;
	int8_t color;
	bool occ;
	int8_t pcolor;
	bool pking;

	plot();

	plot(int8_t c, int8_t r);

	/**
		set occupied of plot to true.
		@param pc color of piece that moved in
		@param king is the piece that moved in a king
	*/
	void piece_in(int8_t pc,bool king);

	/**
		set occupied of plot to false.
	*/
	void piece_out();

	void operator=(plot s)
	{
		c = s.c;
		r = s.r;
		color = s.color;
		occ = s.occ;
		pcolor = s.pcolor;
		pking = s.pking;
		
	}

	bool operator==(plot s)
	{
		return (r == s.r && c == s.c);
	}
};

enum color
{
	DARK = 0,
	LIGHT = 1,
	Null = 2
};