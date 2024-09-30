#include "Game.h"
#include "BoardImage.h"
#include <set>
#include <algorithm>
#include "CheckersRules.h"
#include <iostream>
#include "AI.h"

SDL_Window* GameWindow;
SDL_Surface* GameSurface;
Settings GameSettings;
int GameState;
Board GameBoard;
int GameMode;

plot prevClick;
Move prevMove;
std::vector<Move> nextMove;
std::vector<plot> nextMovePlot;

//current turn
int turn;


void clearPlot(plot* p)
{
	p->c = 0;
	p->color = 0;
	p->occ = 0;
	p->pcolor = 0;
	p->pking = 0;
	p->r = 0;
}
bool isPlotClear(plot p)
{
	return ((p.c == 0) || (p.r == 0));
}



void HandleMouseClick(SDL_Event event)
{
	SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
	SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
	SDL_FreeSurface(temp_Sur);
	SDL_UpdateWindowSurface(GameWindow);
	if (event.button.type == SDL_MOUSEBUTTONUP)
	{
		plot CurrClick;
		Board::GetPlotClick(event.button, &CurrClick.c, &CurrClick.r);
		CurrClick = GameBoard.grid[CurrClick.r][CurrClick.c];

		switch (GameState)
		{
		case FIRST:												//looks OK
			{
				if (CurrClick.pcolor != turn)
				{
					return;
				}
				nextMove = GetMovesPiece(GameBoard, CurrClick, GET_ALL);
				if (nextMove.empty())
				{
					Board::highlightPlot(CurrClick, CLR_RED, GameSurface);
					SDL_UpdateWindowSurface(GameWindow);
					break;
				}
				else
				{
					Board::highlightPlot(CurrClick, CLR_BLU, GameSurface);
					nextMovePlot = Move::getFirst(nextMove);
					Board::highlightPlot(nextMovePlot, CLR_YLO, GameSurface);
					SDL_UpdateWindowSurface(GameWindow);
					GameState = SEC;
					prevClick = CurrClick;
					clearPlot(&CurrClick);
					break;
				}
			}


		case SEC:
			{
				auto it = find(nextMovePlot.begin(), nextMovePlot.end(), CurrClick);
				int index = it - nextMovePlot.begin();
				if (it != nextMovePlot.end())			//Selected Move is in move list
				{
					Move thisMove = Move::createMove({ prevClick,CurrClick }, GameBoard);
					if (!IsLegal(GameBoard, thisMove, NOT_SURE))		//illegal move
					{
						if (CurrClick.pcolor == turn)					//select another piece to move
						{
							SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
							SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
							SDL_FreeSurface(temp_Sur);
							clearPlot(&prevClick);
							nextMove.clear();
							nextMovePlot.clear();
							nextMove = GetMovesPiece(GameBoard, CurrClick, GET_ALL);
							prevClick = CurrClick;
							if (nextMove.empty())
							{
								Board::highlightPlot(CurrClick, CLR_RED, GameSurface);
								SDL_UpdateWindowSurface(GameWindow);
								clearPlot(&prevClick);
								nextMove.clear();
								nextMovePlot.clear();
								break;
							}
							else
							{
								Board::highlightPlot(CurrClick, CLR_BLU, GameSurface);
								nextMovePlot = Move::getFirst(nextMove);
								Board::highlightPlot(nextMovePlot, CLR_YLO, GameSurface);
								SDL_UpdateWindowSurface(GameWindow);
								GameState = SEC;
								prevClick = CurrClick;
								break;
							}
						}
						else											//deselecct piece
						{
							SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
							SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
							SDL_FreeSurface(temp_Sur);
							clearPlot(&prevClick);
							nextMove.clear();
							nextMovePlot.clear();
							GameState = FIRST;
						}
					}
					else												//legal Move
					{
						//make move, render to screen, set turn
						GameBoard = Board::MakeMove(GameBoard, thisMove);
						SDL_Surface* temp_Sur= Board::CreateBoardSurface(GameBoard);
						SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
						SDL_FreeSurface(temp_Sur);
						SDL_UpdateWindowSurface(GameWindow);


						if (nextMove[index].multicapture) 
						{
							vector<Move> nMove = GetMovesPiece(GameBoard, CurrClick, GET_CAPTURES);		//check multiple captures
							if (thisMove.capture && (!nMove.empty()) && nextMove[index].multicapture)	//Multiple Captures
							{
								GameState = MID;
								prevClick = CurrClick;
								prevMove = thisMove;
								nextMove = nMove;
								nextMovePlot = Move::getFirst(nMove);

								Board::highlightPlot(CurrClick, CLR_BLU, GameSurface);
								Board::highlightPlot(nextMovePlot, CLR_YLO, GameSurface);
								SDL_UpdateWindowSurface(GameWindow);
								break;
							}
						}
						else
						{
							if (turn == DARK)	turn = LIGHT;
							else
							{
								turn = DARK;
							}
							GameState = FIRST;
							clearPlot(&prevClick);
							nextMove.clear();
							nextMovePlot.clear();
							prevMove.src.c = 0;
							SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
							SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
							SDL_FreeSurface(temp_Sur);
							SDL_UpdateWindowSurface(GameWindow);
							break;
						}
					}
						

				}
				else
				{
					if (CurrClick.pcolor == turn)
					{
						SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
						SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
						SDL_FreeSurface(temp_Sur);
						SDL_UpdateWindowSurface(GameWindow);
						clearPlot(&prevClick);
						nextMove.clear();
						nextMovePlot.clear();
						nextMove = GetMovesPiece(GameBoard, CurrClick, GET_ALL);
						if (nextMove.empty())
						{
							Board::highlightPlot(CurrClick, CLR_RED, GameSurface);
							clearPlot(&prevClick);
							nextMove.clear();
							nextMovePlot.clear();
							break;
						}
						else
						{
							Board::highlightPlot(CurrClick, CLR_BLU, GameSurface);
							nextMovePlot = Move::getFirst(nextMove);
							Board::highlightPlot(nextMovePlot, CLR_YLO, GameSurface);
							GameState = SEC;
							prevClick = CurrClick;
							break;
						}
						SDL_UpdateWindowSurface(GameWindow);
					}
					else
					{
						//Board::clearHighlight();
						SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
						SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
						SDL_FreeSurface(temp_Sur);
						SDL_UpdateWindowSurface(GameWindow);
						clearPlot(&prevClick);
						nextMove.clear();
						nextMovePlot.clear();
						GameState = FIRST;
						break;
					}
				}
			}

		case MID:
			{
				if (find(nextMovePlot.begin(),
					nextMovePlot.end(), CurrClick) != nextMovePlot.end())
				{
					Move thisMove = Move::createMove({ prevClick,CurrClick }, GameBoard);
					if (IsLegal(GameBoard, thisMove, NOT_SURE))
					{
						GameBoard = Board::MakeMove(GameBoard, thisMove);
						SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
						SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
						SDL_FreeSurface(temp_Sur);

						std::vector<Move> nMove = GetMovesPiece(GameBoard, CurrClick, GET_CAPTURES);
						if (nMove.empty())
						{
							clearPlot(&prevClick);
							clearPlot(&prevMove.dst);
							clearPlot(&prevMove.src);
							nextMove.clear();
							nextMovePlot.clear();
							GameState = FIRST;
							if (turn == DARK)	turn = LIGHT;
							else			turn = DARK;
							break;
						}
						else
						{
							nextMove = nMove;
							nextMovePlot = Move::getFirst(nMove);
							prevClick = CurrClick;
							prevMove = thisMove;
							GameState = MID;
							Board::highlightPlot(CurrClick, CLR_BLU, GameSurface);
							Board::highlightPlot(nextMovePlot, CLR_YLO, GameSurface);
							break;
						}
						break;
					}
				}
				else
				{
					Board::highlightPlot(CurrClick, CLR_RED, GameSurface);
				}
			}
		}
	}
}

void InitGame(Settings sets, int gameMode)
{
	Board brd;
	int clr;
	if (sets.player1 == DARK)
	{
		clr = LIGHT;
	}
	else
	{
		clr = DARK;
	}

	brd = Board::createBoard(clr);
	GameBoard = brd;
	GameState = FIRST;
	turn = DARK;
	GameSettings = sets;
	GameMode = gameMode;
	clearPlot(&prevClick);
	nextMove.clear();
	nextMovePlot.clear();

	if (GameSurface != NULL)		SDL_FreeSurface(GameSurface);
	if (GameWindow != NULL)
	{
		SDL_DestroyWindow(GameWindow);
	}
	GameWindow = SDL_CreateWindow("CHECKERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SURFACE_D, BOARD_SURFACE_D, SDL_WINDOW_HIDDEN);
	GameSurface = SDL_GetWindowSurface(GameWindow);

	try
	{
		SDL_Surface* surface = Board::CreateBoardSurface(GameBoard);
		SDL_BlitSurface(surface, NULL, GameSurface, NULL);
		SDL_UpdateWindowSurface(GameWindow);
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	catch(...){

	}
	
}

//Return INT_MAX on draw
int win()
{
	if (GameBoard.pcDark == 0) return LIGHT;
	else if (GameBoard.pcLight == 0) return DARK;
	else if (GetAllMoves(GameBoard, turn, GET_ALL).size() == 0)	return ((turn == DARK) ? LIGHT : DARK);
	else return Null;
}


Move GetAIMove(Board GameBoard, int TurnColor)
{
	/*
	//std::cout << "Generating moves of color: " << TurnColor << "\n";
	vector<Move> LegalMoves = GetAllMoves(GameBoard, TurnColor, GET_ALL);
	int size = LegalMoves.size();
	int index = (rand() % size);
	return LegalMoves[index];*/
	return AI::GetBestMove(GameBoard, TurnColor);
}

