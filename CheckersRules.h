#pragma once
#include "Board.h"
#include "plot.h"
#include "Move.h"
#include <vector>

using namespace std;


//functions of this header
//get all possible moves
//is legal
//get moves of single piece

/**
	Gets all possible moves of a color
	@param brd the current game board
	@param color the color with current turn
	@param flags get all moves or just captures. can be GET_CAPTURES or GET_ALL
	@return a vector of possible moves
*/
vector <Move> GetAllMoves(Board brd,int8_t color,int flags);



/**
	Gets all possible moves of a piece
	@param brd the current game board
	@param piece the piece to move(plot)
	@param flags get all moves or just captures. can be GET_CAPTURES or GET_ALL
	@return a vector of possible moves
*/
vector<Move> GetMovesPiece(Board brd, plot piece,int flags);


/**
	Checks whether move is legal or not
	@param brd The current game board
	@param move Move to be checked
	@param cptStatus Is a capture of the color possible or not 
					TRUE for yes, FLASE for no, NOT_SURE to check
	@return returns true if move is legal else returns false
*/
bool IsLegal(Board brd, Move move,int cptStatus);

/**
	Checks whether capture is possible or not.
	@param brd The current game board
	@param color Color with current turn.
	@return returns true if capture is possible else returns false
*/
bool IsCapturePossible(Board brd, int mpveClr);

enum MoveDirection
{
	UP,
	DOWN
};

enum GetMoveFlags
{
	GET_CAPTURES = 1,
	GET_ALL = 2
};

enum boolStatus
{
	FALSE = 0,
	TRUE = 1,
	NOT_SURE = -1
};