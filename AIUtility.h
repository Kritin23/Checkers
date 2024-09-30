#pragma once

#include "Board.h"
#include "Move.h"
#include <vector>
#include <algorithm>

typedef std::vector<std::pair<Move, Board>> VP_Move_Board;

const int hashPrime = 3;
const int hashMod = 10000019;

struct AIBoard
{
	signed char grid[33];
	/*
	stores all pieces as an array (only dark squares)
	start numbering from top left
	*/

	char pcDark;
	char pcLight;
};

class AIUtility
{
public:
	

	static long long hashPrimePowers[33];
	static int evals[hashMod];

	static void initAI()
	{
		for (int i = 0; i < 33; i++)
		{
			hashPrimePowers[i] = 0;
		}
		for (int i = 0; i < hashMod; i++)
		{

			/*
			0 evaluation is possible and common, 
			but since evaluation is multiplied by 100, evaluation of -1 is unlikely*/
			evals[i] = -1;
		}

	}

	//return boards after making all possible moves
	static VP_Move_Board	MoveGeneration(Board brd, int turn);

	//input a board 
	static Board ConsoleBoardInput();
	
	static AIBoard BoardToAIBoard(Board brd);

	static Board AIBoardToBoard(AIBoard brd);


	static long getTime()
	{
		return (SDL_GetTicks()) / 1000;
	}

	static int GetEvalPositionMultiplier(int r, int c)
	{
		const int EvalPositionMultiplier[9][9] =
		{
			{0,   0,   0,   0,   0,   0,   0,   0,   0},
			{0,   0, 125,   0, 120,   0, 120,   0, 120},
			{0, 115,   0, 110,   0, 110,   0, 110,   0},
			{0,   0, 100,   0, 100,   0, 100,   0, 107},
			{0, 105,   0, 107,   0, 107,   0, 100,   0},
			{0,   0, 100,   0, 107,   0, 107,   0, 105},
			{0, 107,   0, 100,   0, 100,   0, 100,   0},
			{0,   0, 110,   0, 110,   0, 110,   0, 115},
			{0, 120,   0, 120,   0, 120,   0, 125,   0}
		};

		return EvalPositionMultiplier[r][c];
	}

	static long long Hash(Board brd);
	static long long powmod(int n);
};

