#pragma once
#include <utility>
#include <vector>
#include "plot.h"

class Board;

class Move
{
public:
	plot src;
	plot dst;
	bool capture;
	bool legal;
	bool multicapture;
	bool makeKing;
	std::vector<plot> captured;
	std::vector<plot> multimovePlot;	//excluding src and dst
	std::vector<bool> capturedIsKing;	//stores whether captured piece is king.
										//in the order captured

	static Move createMove(std::vector<plot> moveSeq,Board brd);
	static Move addMove(Move first, Move second,Board brd);
	static plot getFirst(Move thismove);
	static std::vector<plot> getFirst(std::vector<Move> Movevec);
	static bool kingMove(Move thisMove,const Board& brd); //Move is a kinging move and peice moves after becoming king
	static bool kingingMove(Move thisMove, const Board& brd); //Move ends with a piece not king becoming king
	bool operator==(Move b)
	{
		return (src == b.src && dst == b.dst);
	}
};

