#include "AI.h"
#include "Game.h"
#include <algorithm>
#include <climits>
#include <deque>
#include <ctime>


int AI::moveCounter;
long AI::StartTime;
int AI::projectedEval;
std::vector<Move> AI::storedMoves;

/*order the moves*/
Move AI::GetBestMove(Board brd, int8_t turn)
{
	auto StartTime = std::time(0);
	std::vector<Move> moveList = GetAllMoves(brd, turn, GET_ALL);
	if (moveList.empty())	return Move::createMove({}, brd);

	moveList = AI::MoveOrdering(brd, moveList, true);
	int max_depth = 6;
	if (brd.pcDark + brd.pcLight <= 6)	max_depth = 10;
	
	moveCounter = 0;
	projectedEval = 0;
	//alpha - best for curr_turn, beta - best for opp_turn
	int alpha = INT_MIN + 1, beta = INT_MAX;
	
	Move BestMove = moveList[0];
	
	int oppTurn = (turn == DARK) ? LIGHT : DARK;

	for (auto it : moveList)
	{
		brd = Board::MakeMove(brd, it);
		moveCounter++;
		int eval = -Search(brd, oppTurn, max_depth - 1, -beta, -alpha, max_depth - 2);
		
		if (eval > alpha) { BestMove = it;	projectedEval = eval; }
		
		alpha = std::max(eval, alpha);
		//beta = std::min(eval, beta);

		brd = brd.UnMakeMove(brd, it);
		
		if (std::time(0) - StartTime > MAX_TIME)
			break;
	}

	return BestMove;
}

int AI::Search(Board brd, int8_t turn, int8_t depth = MAX_DEPTH, int alpha = (INT_MIN + 1), int beta = INT_MAX, int storeDepth = MAX_DEPTH - 2)
{
	if (depth == 0)	return AI::EvalPosition(brd, turn);
	std::vector<Move> MoveList = GetAllMoves(brd, turn, GET_ALL);
	MoveList = AI::MoveOrdering(brd, MoveList, false);

	if (MoveList.empty())
	{
		return INT_MIN + 1;
	}
	std::deque<Move> orderedMoves;

	int oppTurn = (turn == DARK) ? LIGHT : DARK;
	for (auto it : MoveList)
	{
		brd = Board::MakeMove(brd, it);
		moveCounter++;
		int eval = -Search(brd, oppTurn, depth - 1, -beta, -alpha, storeDepth);
		if (eval >= beta)
		{
			return beta;
		}
		alpha = std::max(eval, alpha);

		if(depth == storeDepth)
		{
			if (eval == alpha)
			{
				orderedMoves.push_front(it);
			}
			else
			{
				orderedMoves.push_back(it);
			}
		}
		brd = brd.UnMakeMove(brd, it);
	}
	if (depth == 6)
	{
		int x = 0;
	}
	//std::copy(orderedMoves.begin(), orderedMoves.end(), back_inserter(storedMoves));
	return alpha;
}

int AI::EvalPosition(Board brd, int8_t turn)
{

	int Eval = 0;
	for (auto it : brd.Piece[turn])
	{
		Eval += ((int)it.pking + 1) * AIUtility::GetEvalPositionMultiplier(it.r,it.c);
	}
	int8_t oppTurn = (turn == DARK) ? LIGHT : DARK;
	for (auto it : brd.Piece[oppTurn])
	{
		Eval -= ((int)it.pking + 1) * AIUtility::GetEvalPositionMultiplier(it.r, it.c);
	}

	return Eval;

}

std::vector<Move> AI::MoveOrdering(const Board& brd, std::vector<Move> moves, bool useStoredMoves)
{
	std::vector<Move> priorityMoves, regularMoves, orderedMoves;
	if (moves.empty())	return moves;

	
	if (!AI::storedMoves.empty() && useStoredMoves)
	{
		for (auto it : AI::storedMoves)
		{
			auto itm = std::find(moves.begin(), moves.end(), it);
			{
				if (itm != moves.end())	priorityMoves.push_back(*itm);
				moves.erase(itm);
			}
		}

		AI::storedMoves.clear();
	}


	if(!moves[0].capture)
	{
		for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++)
		{
			if (Move::kingingMove(*it, brd))
			{
				priorityMoves.push_back(*it);
				//moves.erase(it);
			}
			else
			{
				regularMoves.push_back(*it);
			}
		}
		for (auto it : priorityMoves)	orderedMoves.push_back(it);
		for (auto it : regularMoves)	orderedMoves.push_back(it);
		return orderedMoves;
	}
	else
	{
		for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); it++)
		{
			plot capt = brd.grid[(it->src.r + it->dst.r) / 2][(it->src.c + it->dst.c) / 2];
			if (Move::kingingMove(*it, brd) || it->multicapture || capt.pking)
			{
				orderedMoves.push_back(*it);
			}
			else
			{
				regularMoves.push_back(*it);
			}
		}
		for (auto it : priorityMoves)	orderedMoves.push_back(it);
		for (auto it : regularMoves)	orderedMoves.push_back(it);
		return orderedMoves;
	}
}
