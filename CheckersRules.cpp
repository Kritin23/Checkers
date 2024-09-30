#include "CheckersRules.h"
#include "Board.h"
#include <cmath>

using namespace std;


//here
vector<Move> GetAllMoves(Board brd, int8_t color, int flags)
{
	vector<Move> final;
	for (auto it = brd.Piece[color].begin(); it != brd.Piece[color].end(); it++)
	{
		int i = it->r;
		int j = it->c;
		vector<Move> temp;
		temp = GetMovesPiece(brd, brd.grid[i][j], flags);
		final.insert(final.end(), temp.begin(), temp.end());
	}
			
	return final;
}

vector<Move> GetMovesPiece(Board brd, plot piece, int flags)
{
	vector<Move> allMoves = {};

	piece = brd.grid[piece.r][piece.c];

	int cptrStatus;
	if (IsCapturePossible(brd, piece.pcolor)==TRUE)
	{
		cptrStatus = TRUE;
	}
	else
	{
		cptrStatus = FALSE;
	}

	plot src;
	src.c = piece.c;
	src.r = piece.r;
	plot dst;
	Move* move;
	if (cptrStatus==TRUE)
	{
		src = piece;
		
		//top right
		if (piece.r > 2 && piece.c < 7)		//change here
		{
			move = new Move;

			dst = brd.grid[piece.r - 2][piece.c + 2];		//and here

			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				Board brdt = Board::MakeMove(brd, *move);
				move->capturedIsKing.clear();
				vector<Move> movet = {};
				if(!Move::kingingMove(*move,brd))	movet = GetMovesPiece(brdt, dst, GET_CAPTURES);
				if (movet.empty())			
				{
					if(IsLegal(brd,*move,cptrStatus))	allMoves.push_back(*move);
				}
				else
				{
					for (auto it = movet.begin(); it != movet.end(); it++)
					{
						Move movet = Move::addMove(*move, *it, brd);
						if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(movet);
					}
				}
			}
			delete move;
			move = NULL;
		}

		//top left
		if (piece.r > 2 && piece.c > 2)		//change here
		{
			move = new Move;

			dst = brd.grid[piece.r - 2][piece.c - 2];		//and here

			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				Board brdt = Board::MakeMove(brd, *move);
				vector<Move> movet = {};
				if (!Move::kingingMove(*move, brd))	movet = GetMovesPiece(brdt, dst, GET_CAPTURES);
				for (auto it = movet.begin(); it != movet.end(); it++)
				{
					Move movet = Move::addMove(*move, *it, brd);
					if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(movet);
				}
				if (movet.empty())
				{
					if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
				}
			}
			delete move;
			move = NULL;
		}

		//bottom left
		if (piece.r < 7 && piece.c > 2)		//change here
		{
			move = new Move;

			dst = brd.grid[piece.r + 2][piece.c - 2];		//and here

			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				Board brdt = Board::MakeMove(brd, *move);
				vector<Move> movet = {};
				if (!Move::kingingMove(*move,brd))	movet = GetMovesPiece(brdt, dst, GET_CAPTURES);
				for (auto it = movet.begin(); it != movet.end(); it++)
				{
					Move movet = Move::addMove(*move, *it, brd);
					if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(movet);
				}
				if (movet.empty())
				{
					if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
				}
			}
			delete move;
			move = NULL;
		}

		//bottom right
		if (piece.r < 7 && piece.c < 7)		//change here
		{
			move = new Move;

			dst = brd.grid[piece.r + 2][piece.c + 2];		//and here

			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				Board brdt = Board::MakeMove(brd, *move);
				vector<Move> movet = {};
				if (!Move::kingingMove(*move,brd))	movet = GetMovesPiece(brdt, dst, GET_CAPTURES);
				for (auto it = movet.begin(); it != movet.end(); it++)
				{
					Move movet = Move::addMove(*move, *it, brd);
					if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(movet);
				}
				if (movet.empty())
				{
					if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
				}
			}
			delete move;
			move = NULL;
		}
	}
	if (cptrStatus == FALSE && flags == GET_ALL)
	{
		
		//top left
		if (piece.r > 1 && piece.c > 1)
		{
			
			dst = brd.grid[piece.r - 1][piece.c - 1];	//change here
			move = new Move;
			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move , cptrStatus))
			{
				if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
			}
			delete move;
			move = NULL;
		}


		//top right
		if (piece.r > 1 && piece.c < 8)
		{
			
			dst = brd.grid[piece.r - 1][piece.c + 1];	//change here
			move = new Move;
			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
			}
			delete move;
			move = NULL;
		}


		//bottom left
		if (piece.r < 8 && piece.c > 1)
		{
			
			dst = brd.grid[piece.r + 1][piece.c - 1];	//change here
			move = new Move;
			vector<plot> moveplot = { src,dst };
			*move = Move::createMove(moveplot, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
			}
			delete move;
			move = NULL;
		}


		//bottom right
		if (piece.r < 8 && piece.c < 8)
		{
			
			dst = brd.grid[piece.r + 1][piece.c + 1];	//change here
			move = new Move;
			*move = Move::createMove({ src,dst }, brd);
			if (IsLegal(brd, *move, cptrStatus))
			{
				if (IsLegal(brd, *move, cptrStatus))	allMoves.push_back(*move);
			}
			delete move;
			move = NULL;
		}
	}

	return allMoves;
}

bool IsLegal(Board brd, Move move,int cptStatus)
{
	bool returnv=true;
	//if (!move.legal)	returnv= false;
	COORD_U src = { move.src.r , move.src.c };
	COORD_U dst = { move.dst.r,move.dst.c };

	//move out of the board
	if (src.first > 8 || src.second > 8
		|| src.second < 1 || src.first < 1
		|| dst.first>8 || dst.second>8
		|| dst.second < 1 || dst.first < 1
		)		returnv=false;
	
	//moving on a light square
	if ((brd.grid[src.first][src.second].color == LIGHT) || (brd.grid[dst.first][dst.second].color == LIGHT))	returnv = false;

	//moving up or down
	int UpOrDown;
	if (move.src.pcolor == brd.sidecR1)	UpOrDown = DOWN;
	else								UpOrDown = UP;

	//not a king and moving backwards
	if (!move.src.pking)
	{
		if ((UpOrDown == UP && (dst.first > src.first)) || (UpOrDown == DOWN && (dst.first < src.first)))
		{
			returnv=false;
		}
	}


	//destination is occupied
	if (brd.grid[dst.first][dst.second].occ)	returnv= false;

	std::vector<plot> captured = move.captured;
	int moveClr = brd.grid[src.first][src.second].pcolor;

	//move is not a capture
	if (!move.capture)
	{

		//capture is possible
		if (cptStatus == TRUE)	return false;
		else if (cptStatus == NOT_SURE)
		{
			if (IsCapturePossible(brd, moveClr))	returnv=false;
		}
		{
			//moving >1 square
			if ((abs(dst.first - src.first) != 1) || abs(dst.second - src.second) != 1)
			{
				returnv=false;
			}
		}
	}
	//move is a capture
	else
	{
		//move is not multiple capture
		if (!move.multicapture)
		{
			//move >2 square diagonally
			if ((abs(dst.first - src.first) != 2) || abs(dst.second - src.second) != 2)
			{
				returnv=false;
			}

			//square jumped is empty or occ by same color
			if( !brd.grid[ (dst.first+src.first) /2][ (dst.second+src.second) /2].occ 
				|| 
				brd.grid[(dst.first + src.first) / 2][ (dst.second + src.second) / 2].pcolor == moveClr)
			{
				returnv=false;
			}


		}
		//multiple capture move
		else
		{
			
			plot prev;
			prev = brd.grid[src.first][src.second];

			for (auto it = move.multimovePlot.begin(); it != move.multimovePlot.end(); it++)
			{
				//move out of the board
				if (it->r > 8 || it->c > 8 || it->r < 1 || it->c < 1)	returnv= false;

				//moving on a light square
				if (it->color == LIGHT)		returnv= false;

				//jumped >2 diagonally
				if (!(abs(it->r - prev.r) == 2 && abs(it->c - prev.c) == 2))	returnv= false;

				
				//intermediate plots occ
				if (brd.grid[it->r][it->c].occ)	returnv= false;
				

				//not a king and moved backwards
				if (!move.src.pking)
				{
					if ((UpOrDown == UP && (it->r > prev.r)) || (UpOrDown == DOWN && (it->r < prev.r)))
					{
						returnv = false;
					}
				}

				//piece a man reached end and continued
				if (!move.src.pking)
				{
					int r;
					if (UpOrDown == UP)	r = 1;
					else				r = 8;

					if (it->r == r)	returnv= false;
				}
				prev = *it;
			}
			//comp dst and prev
			//jumped >2 diagonally
			if (!(abs(dst.first- prev.r) == 2 && abs(dst.second - prev.c) == 2))	returnv = false;
			if (!move.src.pking)
			{
				if ((UpOrDown == UP && (dst.first > prev.r)) || (UpOrDown == DOWN && (dst.first < prev.r)))
				{
					returnv = false;
				}
			}




			if (!(abs(dst.first - prev.r) == 2 && abs(dst.second - prev.c) == 2))	returnv=false;


			//jumped plots are empty or occ by same color
			//plot out of the board
			for (auto it = move.captured.begin(); it != move.captured.end(); it++)
			{
				//out of board
				if (it->r > 8 || it->c > 8 || it->r < 1 || it->c < 1)	returnv= false;

				//empty
				if (it->occ == false)		returnv= false;

				//occ by same color
				if (it->pcolor == moveClr)	returnv= false;

			}


		}
	}
	//if move is a kinging move
	if (Move::kingMove(move, brd))
	{
		returnv=false;
	}

	if (returnv == false)
	{
		
		return false;
	}
	else
	{
		return true;
	}
}

bool IsCapturePossible(Board brd, int moveClr)
{
	int UpDown;
	int oppClr;

	//set UPDown
	if (brd.sidecR1 == moveClr)
	{
		UpDown = DOWN;
	}
	else
	{
		UpDown = UP;
	}
	
	//set oppClr
	if (moveClr == DARK)
	{
		oppClr = LIGHT;
	}
	else
	{
		oppClr = DARK;
	}

	for (auto it = brd.Piece[moveClr].begin(); it != brd.Piece[moveClr].end(); it++)
	{
		int row = it->r;
		int col = it->c;
		//check capture

		//going up
		if (((UpDown == UP) || (UpDown == DOWN && brd.grid[row][col].pking)) && row > 2)
		{

			if (col > 2)
			{
				if (brd.grid[row - 1][col - 1].pcolor == oppClr && !brd.grid[row - 2][col - 2].occ)		return TRUE;
			}
			if (col < 7)
			{
				if (brd.grid[row - 1][col + 1].pcolor == oppClr && !brd.grid[row - 2][col + 2].occ)		return TRUE;
			}

		}

		//going down
		if (((UpDown == DOWN) || (UpDown == UP && brd.grid[row][col].pking)) && row < 7)
		{
			if (col > 2)
			{
				if (brd.grid[row + 1][col - 1].pcolor == oppClr && !brd.grid[row + 2][col - 2].occ)		return TRUE;
			}
			if (col < 7)
			{
				if (brd.grid[row + 1][col + 1].pcolor == oppClr && !brd.grid[row + 2][col + 2].occ)		return TRUE;
			}

		}
	}
				
	return FALSE;
}

