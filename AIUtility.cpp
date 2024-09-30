#include "AIUtility.h"
#include <iostream>
#include "CheckersRules.h"

long long AIUtility::hashPrimePowers[33];
int AIUtility::evals[hashMod];

VP_Move_Board AIUtility::MoveGeneration(Board brd, int turn)
{
	VP_Move_Board  returnVal;
	std::vector<Move> Moves = GetAllMoves(brd, turn, GET_ALL);
	for (auto it:Moves) {
		returnVal.push_back({ it,std::move(Board::MakeMove(brd, it)) });
	}
	return returnVal;
}

Board AIUtility::ConsoleBoardInput()
{
	int R1Clr = LIGHT;
	int R8Clr = DARK;
	Board brd;
	short LightCount = 0;
	short DarkCount = 0;
	brd = Board::createBoard(R1Clr);
	for (int i = 1;i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{

			int x;
			std::cin >> x;
			bool pking = false;
			if ((i == 1 && x == R8Clr) || (i == 8 && x == R1Clr))	pking = true;
			brd.grid[i][j].r = i;
			brd.grid[i][j].c = j;
			brd.grid[i][j].piece_in(x, pking);
			
			if (x == LIGHT)
			{
				brd.Piece[LIGHT].push_back(brd.grid[i][j]);
				LightCount++;
			}
			if (x == DARK)
			{
				brd.Piece[DARK].push_back(brd.grid[i][j]);
				DarkCount++;
			}
		}
	}
	brd.pcDark = DarkCount;
	brd.pcLight = LightCount;
	return brd;
}

long long AIUtility::Hash(Board brd)
{
	long long hash = 0;
	for (auto it : brd.Piece[DARK])
	{
		hash += 1 * powmod(it.r * 4 + it.c - (it.r % 2));
		hash = hash % hashMod;
	}
	for (auto it : brd.Piece[LIGHT])
	{
		hash += 2 * powmod(it.r * 4 + it.c - (it.r % 2) - 1);
		hash = hash % hashMod;
	}
	return hash;
}

long long AIUtility::powmod(int n)
{
	if (n == 0) return 1;
	if (n == 1) return hashPrime;
	else
	{
		if (hashPrimePowers[n] != 0)	return hashPrimePowers[n];
		else
		{
			long long x = (powmod(n / 2) * powmod(n / 2))%hashMod;
			if (n / 2 == 0)
			{
				hashPrimePowers[n] = x;
				return x;
			}
			else
			{
				hashPrimePowers[n] = (x*hashPrime)%hashMod;
				return x;
			}

		}
	}
}

