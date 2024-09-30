#pragma once

#include "Board.h"
#include "AIUtility.h"
#include <iostream>
#include "CheckersRules.h"

class AI
{
private:
	static const int MAX_DEPTH = 10;
	static const long MAX_TIME = 5;//seconds
	static int moveCounter;
	static long StartTime;
	static int projectedEval;
	static std::vector<Move> storedMoves; //Stores moves of curr+2. used for move_ordering

public:
	static Move GetBestMove(Board brd, int8_t turn);
	static int Search(Board brd, int8_t turn, int8_t depth, int alpha, int beta, int storeDepth);
	static int EvalPosition(Board brd, int8_t turn);
	static std::vector<Move> MoveOrdering(const Board& brd, std::vector<Move> moves, bool useStoredMoves);
	static void init()
	{
		moveCounter = 0;
		storedMoves = {};
	}
	static int getMoveCount()
	{
		return moveCounter;
	}
	static int getProjectedEval()
	{
		return projectedEval;
	}
};

