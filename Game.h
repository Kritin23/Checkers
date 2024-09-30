/**
This file will contain Game loop and related
*/

#pragma once
#include "Board.h"
#include <SDL.h>
#include "Settings.h"
#include <vector>
#include "AI.h"

extern SDL_Window* GameWindow;
extern SDL_Surface* GameSurface;
extern Settings GameSettings;
extern int GameState;
extern Board GameBoard;
extern int GameMode;

extern plot prevClick;
extern Move prevMove;
extern std::vector<Move> nextMove;
extern std::vector<plot> nextMovePlot;

extern int turn;


enum GameState
{
	FIRST,
	SEC,
	MID,
};

enum gameMode
{
	MULTIP,
	SINGLEP

};


//Handles Mouse Click Events, Makes The moves, and renders to screen.
//sets new board in GameBoard
//set turn before calling 
void HandleMouseClick(SDL_Event event);

void InitGame(Settings sets, int gameMode);

//return INT_MAX on DRAW
int win();

Move GetAIMove(Board board, int TurnColour);