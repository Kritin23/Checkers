#include "Board.h"
#include <SDL.h>
#include "BoardImage.h"
#include <algorithm>
#include <utility>
#include "CheckersRules.h"
#include <string>

std::vector<plot> highlighted;

//here
Board Board::createBoard(int colorRow1)
{
	Board thisbrd;

	//set colour this side and that side...  this side is down and that side is up ... row 1 is up
	int clrt, clro;
	clrt = DARK;
	clro = LIGHT;
	if (colorRow1 == DARK)
	{
		std::swap(clro, clrt);
	}
	int pieceCount[3] = { 0,0,0 };

	//begin iteration
	for(int i=1;i<=8;i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			//set variables
			
				int plot_clr = Null;
				int pc_clr = Null;
				int col = j;
				int row = i;

				//set plot color
				if (((i + j) % 2) == 0) plot_clr = LIGHT;
				else
				{
					plot_clr = DARK;
				}

				//set pc color
				if (plot_clr == DARK)
				{
					if (i <= 3)			pc_clr = clro;
					else if (i > 5)		pc_clr = clrt;
					else				pc_clr = Null;
				}
				else				pc_clr = Null;
			
			//set data
				if (pc_clr == Null)
				{
					thisbrd.grid[i][j].c = col;
					thisbrd.grid[i][j].r = row;
					thisbrd.grid[i][j].color = plot_clr;
					thisbrd.grid[i][j].piece_out();

				}
				else
				{
					thisbrd.grid[i][j].c = col;
					thisbrd.grid[i][j].r = row;
					thisbrd.grid[i][j].color = plot_clr;
					thisbrd.grid[i][j].piece_in(pc_clr,false);
					thisbrd.grid[i][j].pking = false;

					//over here
					thisbrd.Piece[pc_clr].push_back(thisbrd.grid[i][j]);
					pieceCount[pc_clr]++;

				}
			
		}
	}
	thisbrd.sidecR1 = clro;
	thisbrd.pcDark = 12;
	thisbrd.pcLight = 12;

	return thisbrd;
}

SDL_Surface* Board::CreateBoardSurface(Board board)

{
	SDL_Surface* fsurface = boardImg::CreateboardImg(GameSettings.BrdImg);
	string DS = GameSettings.location + "CheckerDark.bmp";
	string LS = GameSettings.location + "CheckerLight.bmp";
	string KL = GameSettings.location + "CheckerKingLight.bmp";
	string KD = GameSettings.location + "CheckerKingDark.bmp";
	SDL_Surface* CheckerDS = SDL_LoadBMP(DS.c_str());
	SDL_Surface* CheckerLS = SDL_LoadBMP(LS.c_str());
	SDL_Surface* CheckerKLS = SDL_LoadBMP(KL.c_str());
	SDL_Surface* CheckerKDS = SDL_LoadBMP(KD.c_str());

	Uint32 colorCheckerBckg = SDL_MapRGB(CheckerLS->format, 0x66, 0xFF, 0x11);
	SDL_SetColorKey(CheckerDS, SDL_TRUE, colorCheckerBckg);
	SDL_SetColorKey(CheckerLS, SDL_TRUE, colorCheckerBckg);
	SDL_SetColorKey(CheckerKDS, SDL_TRUE, colorCheckerBckg);
	SDL_SetColorKey(CheckerKLS, SDL_TRUE, colorCheckerBckg);

	SDL_Rect piece;
	piece.x = BOARD_BEGIN_C;
	piece.y = BOARD_BEGIN_C;
	piece.h = 64;
	piece.w = 64;

	SDL_Rect rectChecker;
	rectChecker.x = 0;
	rectChecker.y = 0;
	rectChecker.h = TILE_D;
	rectChecker.w = TILE_D;

	SDL_Surface* thissurface=NULL;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			
			piece.y = (TILE_D * (i - 1)) + BOARD_BEGIN_C;
			piece.x = (TILE_D * (j - 1)) + BOARD_BEGIN_C;
			if (board.grid[i][j].occ)
				//switch (board.grid[i][j].pcolor)
			{
				if (board.grid[i][j].pcolor == DARK) 
				{
					if (board.grid[i][j].pking)
					{

						thissurface = CheckerKDS;
						SDL_BlitScaled(thissurface, &rectChecker, fsurface, &piece);
					}
					else
					{

						thissurface = CheckerDS;
						SDL_BlitScaled(thissurface, &rectChecker, fsurface, &piece);
					}
				}

				if (board.grid[i][j].pcolor == LIGHT) 
				{
					if (board.grid[i][j].pking)
					{

						thissurface = CheckerKLS;
						SDL_BlitScaled(thissurface, &rectChecker, fsurface, &piece);
					}
					else
					{
						thissurface = CheckerLS;
						SDL_BlitScaled(thissurface, &rectChecker, fsurface, &piece);
					}
				}
			}
		}
	}
	SDL_FreeSurface(CheckerDS);
	SDL_FreeSurface(CheckerKDS);
	SDL_FreeSurface(CheckerKLS);
	SDL_FreeSurface(CheckerLS);
	return fsurface;



}

void Board::GetPlotClick(SDL_MouseButtonEvent e,int8_t *col,int8_t *row)
{
	if (e.type==SDL_MOUSEBUTTONUP || e.type==SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		x = e.x;
		y = e.y;
		x -= BOARD_BEGIN_C;
		y -= BOARD_BEGIN_C;
		x /= 64;
		y /= 64;
		if (x > 7 || y > 7)
		{
			col = NULL;
			row = NULL;
			return;
		}
		x++;
		y++;
		*col = x;
		*row = y;
		return;
	}
	col = NULL;
	row = NULL;
	return;
}

void Board::GetPlotClick(SDL_MouseButtonEvent e, std::vector<plot> plots, int8_t* col, int8_t* row)
{
	GetPlotClick(e, col, row);
	std::vector<std::pair<int, int>> xy;
	for (auto it = plots.begin(); it != plots.end(); it++)
	{
		xy.push_back({ it->c, it->r });
	}
	std::pair<int, int> click = { *col,*row };
	if (std::find(xy.begin(), xy.end(), click) != xy.end())
	{
		return;
	}
	else
	{
		*col = Null;
		*row = Null;
		return;
	}
}

Board Board::MakeMove(Board brd, Move& move)
{
	if (!IsLegal(brd, move,NOT_SURE))	return brd;		//**************************
	COORD_U src = { move.src.r , move.src.c };
	COORD_U dst = { move.dst.r,move.dst.c };

	int MoveColor = move.src.pcolor;
	int OppColor;
	if (MoveColor == DARK)	OppColor = LIGHT;
	else
	{
		OppColor = DARK;
	}

	bool king = brd.grid[src.first][src.second].pking;

	std::vector<plot> captured = move.captured;

	int moveClr = brd.grid[src.first][src.second].pcolor;
	brd.grid[src.first][src.second].piece_out();
	brd.grid[dst.first][dst.second].piece_in(moveClr,king);
	brd.grid[dst.first][dst.second].pking = king;
	if (move.capture)
	{
		move.capturedIsKing.clear();
		for (auto it = captured.begin(); it != captured.end(); it++)
		{
			if (brd.grid[it->r][it->c].pking)
			{
				move.capturedIsKing.push_back(true);
			}
			else
			{
				move.capturedIsKing.push_back(false);
			}
			auto piece_remove_it = std::find(brd.Piece[OppColor].begin(),
											brd.Piece[OppColor].end(),
											brd.grid[it->r][it->c]);

			brd.Piece[OppColor].erase(piece_remove_it);
			brd.grid[it->r][it->c].piece_out();
			
		}
	}

	//make king
	if (dst.first == 1 || dst.first == 8)
	{
		if (brd.sidecR1 == moveClr && dst.first == 8)
		{
			brd.grid[dst.first][dst.second].piece_in(moveClr, true);
			brd.grid[dst.first][dst.second].pking = true;
			move.makeKing = true;
		}
		else if (brd.sidecR1 != moveClr && dst.first == 1)
		{
			brd.grid[dst.first][dst.second].piece_in(moveClr, true);
			brd.grid[dst.first][dst.second].pking = true;
			move.makeKing = true;
		}
	}

	if (moveClr == LIGHT)
	{
		brd.pcDark -= (int8_t)captured.size();
	}
	else
	{
		brd.pcLight -= (int8_t)captured.size();
	}
	auto piece_move_src_it = std::find(brd.Piece[MoveColor].begin(),
										brd.Piece[MoveColor].end(),
										brd.grid[src.first][src.second]);
	brd.Piece[MoveColor].erase(piece_move_src_it);
	brd.Piece[MoveColor].push_back(brd.grid[dst.first][dst.second]);


	return brd;
}

Board Board::UnMakeMove(Board brd, Move move)
{
	COORD_U dst = { move.dst.r, move.dst.c };
	COORD_U src = { move.src.r, move.src.c };

	int8_t moveClr = brd.grid[dst.first][dst.second].pcolor;
	if (moveClr == Null)	return brd;
	int8_t oppClr = (moveClr == DARK) ? LIGHT : DARK;

	bool movepcIsKing = (brd.grid[dst.first][dst.second].pking) && !move.makeKing;
	brd.grid[dst.first][dst.second].piece_out();
	brd.grid[src.first][src.second].piece_in(moveClr, movepcIsKing);

	auto piece_move_dst_it = std::find(brd.Piece[moveClr].begin(),
		brd.Piece[moveClr].end(),
		brd.grid[dst.first][dst.second]);
	brd.Piece[moveClr].erase(piece_move_dst_it);
	brd.Piece[moveClr].push_back(brd.grid[src.first][src.second]);

	if (move.capture)
	{
		if (move.captured.size() != move.capturedIsKing.size())	return brd;
		for (int i = 0; i < move.captured.size(); i++)
		{
			COORD_U curr = { move.captured[i].r, move.captured[i].c };
			brd.grid[curr.first][curr.second].piece_in(oppClr, move.capturedIsKing[i]);

			brd.Piece[oppClr].push_back(brd.grid[curr.first][curr.second]);
			if (oppClr == DARK)
			{
				brd.pcDark++;
			}
			else
			{
				brd.pcLight++;
			}
		}
	}
	return brd;
}


void Board::highlightPlot(plot plot, int color, SDL_Surface* &GameSurface)
{
	int c = BOARD_BEGIN_C + (plot.c - 1) * TILE_D;
	int r = BOARD_BEGIN_C + (plot.r - 1) * TILE_D;
	SDL_Surface* highlight;
	string file;
	switch (color)
	{
	case CLR_RED:
		file = GameSettings.location + "HighlightRed.bmp";
		break;

	case CLR_YLO:
		file = GameSettings.location + "HighlightYellow.bmp";
		break;

	case CLR_BLU:
		file = GameSettings.location + "HighlightBlue.bmp";
		break;
	}
	
	highlight = SDL_LoadBMP(file.c_str());
	Uint32 colorKey = SDL_MapRGB(highlight->format, 0x66, 0xFF, 0x11);
	SDL_SetColorKey(highlight, SDL_TRUE, colorKey);
	SDL_Rect blitd;
	blitd.x = c;
	blitd.y = r;
	blitd.h = TILE_D;
	blitd.w = TILE_D;

	SDL_Rect blits;
	blits.x = 0;
	blits.y = 0;
	blits.h = TILE_D;
	blits.w = TILE_D;

	SDL_BlitScaled(highlight, &blits, GameSurface, &blitd);
	SDL_FreeSurface(highlight);
	highlight = NULL;
	highlighted.push_back(plot);
}

void Board::highlightPlot(std::vector<plot> plot, int color, SDL_Surface* &GameSurface)
{
	for (auto it = plot.begin(); it != plot.end(); it++)
	{
		highlightPlot(*it, color, GameSurface);
	}
}

void Board::clearHighlight()
{
	SDL_Rect rectArr[32];
	for (int i = 0; i < highlighted.size(); i++)
	{
		rectArr[i].x = BOARD_BEGIN_C+((highlighted[i].c - 1) * TILE_D);
		rectArr[i].y = BOARD_BEGIN_C + ((highlighted[i].r - 1) * TILE_D);
		rectArr[i].h = TILE_D;
		rectArr[i].w = TILE_D;
	}
	SDL_Color clrD = GameSettings.BrdImg.clrDark;
	SDL_FillRects(GameSurface, &rectArr[0], highlighted.size(), SDL_MapRGB(GameSurface->format,clrD.r,clrD.g,clrD.b));
	highlighted.clear();
}
