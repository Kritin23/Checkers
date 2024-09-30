#pragma once

#include "plot.h"
#include <algorithm>
#include <SDL.h>
#include "BoardImage.h"
#include <vector>
#include "Move.h"
#include "Game.h" 

extern Uint32 colorChecker;
extern Uint32 colorCheckerBckg;
extern std::vector<plot> highlighted;

#define COORD_U std::pair<int,int>
// typedef std::pair<int, int> COORD_U;

#define TOTAL_CHECKERS_COUNT 12

class Board
{
public:
	plot grid[9][9];
	int8_t sidecR1;	/**Computer Row or Player2 */
	int8_t pcDark; //no. of pieces
	int8_t pcLight;

	std::vector<plot> Piece[2];	//2D array, first index is Color, DARK or LIGHT, second index is piece ID, 0 to 11

	/**This function creates a new Game Board.
		*ColorRow1 is the color occupied by row 1 (computer or player 2)
		*This function returns a Board.*/
	static Board createBoard(int colorRow1); 
											  
	/**This function creates a board surface with checkers.
	@param boardbackg is the boardImg containing the backgroung of board
	@param board is the Board whose surface you want to create
	@return it returns a SDL_Surface of the board
	*/
	static SDL_Surface* CreateBoardSurface(Board board);

	/** this function gets a plot id from mouse click
	 @param e is SDL_MouseButtonEvent
	 @param *col same as row
	 @param *row are var where plot column and row are stored.
	 col and row are 0 if something other the plots are clicked.
	 should be used in game loop 
	 use SDL_WaitEvent() after this.
	*/
	static void GetPlotClick(SDL_MouseButtonEvent e,int8_t* col,int8_t* row);

	/** this function gets a plot id from specified plots from mouse click
	 @param e is SDL_MouseButtonEvent
	 @param col and row are var where plot column and row are stored.
	 @param plots is vector of plots out of which one is to be selected.
	 col and row are 0 if plot outside the specified plots selected
	 should be used in game loop
	 use SDL_WaitEvent() after this.
	*/
	static void GetPlotClick(SDL_MouseButtonEvent e, std::vector<plot> plots,int8_t* col,int8_t* row);

	/**
		This function makes a move on the board.
		@param brd the current game board.
		@param move the move to make
		@return returns the Board
	*/
	static Board MakeMove(Board brd, Move& move);

	/**
	*	This function un-makes the move on board
	*	move must have been the last made move on the board.
	*/
	static Board UnMakeMove(Board brd, Move move);

	/**
		Highligh a plot of the board
		@param color can be CLR_RED,CLR_YLO,CLR_BLU
	*/
	static void highlightPlot(plot plot, int color, SDL_Surface* &GameSurface);
	static void highlightPlot(std::vector<plot> plot, int color, SDL_Surface* &GameSurface);
	static void clearHighlight();
};

enum HLcolor
{
	CLR_RED,
	CLR_BLU,
	CLR_YLO
};

