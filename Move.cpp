#include "Move.h"
#include "Board.h"

Move Move::createMove(std::vector<plot> moveSeq,Board brd)
{
	Move move;
	move.legal = true;

	
	if (moveSeq.size() < 2)
	{
		move.legal = false;
		return move;
	}

	if (moveSeq.size() == 2)
	{
		move.src = moveSeq.front();
		move.src = brd.grid[move.src.r][move.src.c];
		move.dst = moveSeq.back();
		move.dst = brd.grid[move.dst.r][move.dst.c];

		if (abs(move.dst.c - move.src.c) == 1 && abs(move.dst.r - move.src.r) == 1)
		{
			
			move.capture = false;
			move.multicapture = false;
			return move;
		}

		if (abs(move.src.c - move.dst.c) == 2 &&abs( move.src.r - move.dst.r) == 2)
		{
			move.capture = true;
			move.multicapture = false;
			move.captured = { brd.grid[(move.dst.r + move.src.r) / 2][(move.dst.c + move.src.c) / 2] };
			return move;
		}
		move.legal = false;
		return move;
	}
	if (moveSeq.size() > 2)
	{
		move.multicapture = true;
		move.capture = true;
		
		move.src = moveSeq.front();
		move.src = brd.grid[move.src.r][move.src.c];
		move.dst = moveSeq.back();
		move.dst = brd.grid[move.dst.r][move.dst.c];

		auto it = moveSeq.begin();
		it++;
		auto prev = moveSeq.begin();
		while (it != moveSeq.end())
		{
			int c, r;
			c = it->c;
			r = it->r;
			if (c > 8 || c < 1 || r > 8 || r < 1)
			{
				move.legal = false;
				return move;
			}
			move.multimovePlot.push_back(*it);
			plot bw = brd.grid[(r + prev->r) / 2][(c + prev->c) / 2];
			move.captured.push_back(bw);

			it++;
			prev++;
		}
		move.multimovePlot.pop_back();
		return move;
	}
	move.legal = false;
	return move;
}

Move Move::addMove(Move first, Move second,Board brd)
{
	Move final;
	std::vector<plot> intm;
	final.capture = true;
	final.multicapture = true;

	intm.push_back(first.src);
	intm.insert(intm.end(), first.multimovePlot.begin(), first.multimovePlot.end());
	
	if (first.dst == second.src)
	{
		intm.push_back(first.dst);
	}
	else
	{
		intm.push_back(first.dst);
		intm.push_back(second.src);
	}

	intm.insert(intm.end(), second.multimovePlot.begin(), second.multimovePlot.end());
	intm.push_back(second.dst);
	

	final = createMove(intm, brd);
	return final;
}

plot Move::getFirst(Move thismove)
{
	if (thismove.multicapture)
	{
		return thismove.multimovePlot.front();
	}
	else
	{
		return thismove.dst;
	}
}

std::vector<plot> Move::getFirst(std::vector<Move> Movevec)
{
	std::vector<plot> res;
	for (auto it = Movevec.begin(); it != Movevec.end(); it++)
	{
		res.push_back(Move::getFirst(*it));
	}
	return res;
}

bool Move::kingMove(Move thisMove, const Board& brd)
{
	int targetR = 1;
	if (thisMove.src.occ == false || thisMove.src.pking==true)	return false;
	if (thisMove.src.pcolor == brd.sidecR1)
	{
		targetR = 8;
	}

	//king in between
	if (thisMove.multicapture)
	{
		//thisMove.multimovePlot.push_back(dst);
		for (auto it : thisMove.multimovePlot)
		{
			if (it.r == targetR)	return true;
		}

	}
	return false;
}


bool Move::kingingMove(Move thisMove, const Board& brd)
{
	int targetR = 1;
	if (thisMove.src.pcolor == brd.sidecR1)	targetR = 8;
	if (thisMove.src.pking == false && thisMove.dst.r == targetR)	return true;
	return false;
}