#include "SDL.h"
#include "Board.h"
#include <iostream>
#include "BoardImage.h"
#include <conio.h>
#include "CheckersRules.h"
#include <ctime>
#include "Game.h"
#include "StartScr.h"
#include "AIUtility.h"

using namespace std;

int appState;

#define NDEBUG
//#define DEBUG
//#define TEST


enum GameStateMain
{
	M_DARK_WINS = -1,
	M_QUIT = 0,
	M_LiGHT_WINS = 1,
	M_CONTINUE_GAME = 2,
	M_DRAW = 3
};

/*
//functions
//void startScr(SDL_Color bgclr);			/
						/*return value:
						>1 on start game---sets game variables
						0 on quit 
						
/*
void choosePlayer(SDL_Color bgclr)  /**return -1 on back, 0 on quit, player no. on play
{
	StartW = SDL_CreateWindow("CHECKERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, STARTSCR_W, STARTSCR_H, SDL_WINDOW_SHOWN);
	StartS = SDL_GetWindowSurface(StartW);
	//to be set
	int player=-1;
	int color=Null;

	//colorKey
	SDL_Color clrKey;
	clrKey.r = 0x66;
	clrKey.g = 0xFF;
	clrKey.b = 0x11;


	const int PLAYERS_H = 150;
	const int PLAYERS_W = 300;


	SDL_Rect opRect;
	SDL_Rect tpRect;
	SDL_Rect BBrect;
	//choose no. of player -- screen -- display
	{
		SDL_FillRect(StartS, NULL, SDL_MapRGB(StartS->format, bgclr.r, bgclr.g, bgclr.b));
		int k = -2;
		int y = 50;

		//one player
		opRect.x = (STARTSCR_W / 2) - k - PLAYERS_W;
		opRect.y = y;
		opRect.h = PLAYERS_H;
		opRect.w = PLAYERS_W;
		SDL_Surface* OPS = SDL_LoadBMP("res\\OPlayer.bmp");
		SDL_SetColorKey(OPS, SDL_TRUE, SDL_MapRGB(OPS->format, clrKey.r, clrKey.g, clrKey.b));


		//two player
		tpRect.x = (STARTSCR_W / 2) + k;
		tpRect.y = y;
		tpRect.h = PLAYERS_H;
		tpRect.w = PLAYERS_W;
		SDL_Surface* TPS = SDL_LoadBMP("res\\TPlayer.bmp");
		SDL_SetColorKey(TPS, SDL_TRUE, SDL_MapRGB(TPS->format, clrKey.r, clrKey.g, clrKey.b));


		//back
		BBrect.x = 5;
		BBrect.y = 5;
		BBrect.h = 50;
		BBrect.w = 50;
		SDL_Surface* BackS = SDL_LoadBMP("res\\back.bmp");
		SDL_SetColorKey(BackS, SDL_TRUE, SDL_MapRGB(BackS->format, clrKey.r, clrKey.g, clrKey.b));


		SDL_BlitSurface(OPS, NULL, StartS, &opRect);
		SDL_BlitSurface(TPS, NULL, StartS, &tpRect);
		SDL_Blit	Surface(BackS, NULL, StartS, &BBrect);
		SDL_UpdateWindowSurface(StartW);
		SDL_FreeSurface(OPS);
		SDL_FreeSurface(TPS);
		SDL_FreeSurface(BackS);
	}

	//evt. loop -- choose number of players
	bool quit = false;
	bool back = false;
	SDL_Event evt;
	while (!quit)
	{
		while (SDL_PollEvent(&evt) != 0)
		{
			if (evt.type == SDL_QUIT || (evt.type == SDL_WINDOWEVENT && evt.window.type == SDL_WINDOWEVENT_CLOSE))
			{
				quit = true;
				player = -1;
				back = false;
				appState = QUIT;
			}
			if (evt.type == SDL_MOUSEBUTTONUP)
			{
				SDL_MouseButtonEvent evtb = evt.button;
				int x = evtb.x;
				int y = evtb.y;

				//Back Button
				if (x > BBrect.x && x<(BBrect.x + BBrect.w)
					&& y>BBrect.y&& y < (BBrect.y + BBrect.h))
				{
					quit = true;
					player = -1;
					back = true;
					appState = START_SCREEN;
				}

				//One Player
				if (x > opRect.x&& x<(opRect.x + opRect.w)
					&& y>opRect.y&& y < (opRect.y + opRect.h))
				{
					quit = true;
					player = 1;
					back = false;
				}

				//Two Player
				if (x > tpRect.x&& x<(tpRect.x + tpRect.w)
					&& y>tpRect.y&& y < (tpRect.y + tpRect.h))
				{
					quit = true;
					player = 2;
					back = false;
					appState = PLAY_GAME;
				}
			}

			if (quit) break;
		}
	}
	if (player < 0)
	{
		SDL_FreeSurface(StartS);
		SDL_DestroyWindow(StartW);
		StartW = NULL;
		StartS = NULL;
		return;
	}

	//continue
	if (player == 1) 
	{
		SDL_Rect BBrect;
		SDL_Rect PWdstR;
		SDL_Rect PRdstR;
		//choose color---1 player---display
		{
			SDL_FillRect(StartS, NULL, SDL_MapRGB(StartS->format, bgclr.r, bgclr.g, bgclr.b));

			//PLAYER 1  "PLAY AS..."
			SDL_Surface* pl12S = SDL_LoadBMP("res\\Player12.bmp");
			SDL_SetColorKey(pl12S, SDL_TRUE, SDL_MapRGB(pl12S->format, clrKey.r, clrKey.g, clrKey.b));
			SDL_Rect P1dstRect;
			P1dstRect.x = 10;
			P1dstRect.y = 60;
			P1dstRect.h = 50;
			P1dstRect.w = 260;
			SDL_BlitSurface(pl12S, NULL, StartS, &P1dstRect);
			SDL_FreeSurface(pl12S);

			//back
			
			BBrect.x = 5;
			BBrect.y = 5;
			BBrect.h = 50;
			BBrect.w = 50;
			SDL_Surface* BackS = SDL_LoadBMP("res\\back.bmp");
			SDL_SetColorKey(BackS, SDL_TRUE, SDL_MapRGB(BackS->format, clrKey.r, clrKey.g, clrKey.b));
			SDL_BlitSurface(BackS, NULL, StartS, &BBrect);
			SDL_FreeSurface(BackS);

			//white or red

			//white
			SDL_Rect PWsrcR;
			PWsrcR.x = 0;
			PWsrcR.y = 0;
			PWsrcR.h = 50;
			PWsrcR.w = 150;

			
			PWdstR.x = 20;
			PWdstR.y = 150;
			PWdstR.h = 50;
			PWdstR.w = 150;
			SDL_Surface* BW = SDL_LoadBMP("res\\BW.bmp");
			SDL_BlitSurface(BW, &PWsrcR, StartS, &PWdstR);

			//red
			SDL_Rect PRsrcR;
			PRsrcR.x = 150;
			PRsrcR.y = 0;
			PRsrcR.h = 50;
			PRsrcR.w = 150;

			
			PRdstR.x = 200;
			PRdstR.y = 150;
			PRdstR.h = 50;
			PRdstR.w = 150;
			SDL_BlitSurface(BW, &PRsrcR, StartS, &PRdstR);
			SDL_FreeSurface(BW);


			SDL_UpdateWindowSurface(StartW);
		}

		//event loop
		SDL_Event evt;
		bool end_loop=false;
		bool back=false;
		bool quit=false;
		while (!end_loop)
		{
			while (SDL_PollEvent(&evt) != 0)
			{
				if (evt.type == SDL_QUIT || (evt.type == SDL_WINDOWEVENT && evt.window.type == SDL_WINDOWEVENT_CLOSE))
				{
					end_loop = true;
					quit = true;
					player = 0;
					appState = QUIT;
				}
				else if (evt.type == SDL_MOUSEBUTTONUP)
				{
					int x = evt.button.x;
					int y = evt.button.y;

					//BACK
					if (x >= BBrect.x &&
						x <= (BBrect.x + BBrect.w) &&
						y >= BBrect.y &&
						y <= (BBrect.y + BBrect.h))
					{
						end_loop = true;
						back = true;
						player = -1;
						appState = START_SCREEN;
					}


					//RED
					if (x >= PRdstR.x &&
						x <= (PRdstR.x + PRdstR.w) &&
						y >= PRdstR.y &&
						y <= (PRdstR.y + PRdstR.h))
					{
						end_loop = true;
						color = DARK;
						appState = PLAY_GAME;
					}


					//WHITE
					if (x >= PWdstR.x &&
						x <= (PWdstR.x + PWdstR.w) &&
						y >= PWdstR.y &&
						y <= (PWdstR.y + PWdstR.h))
					{
						end_loop = true;
						color = LIGHT;
						appState = PLAY_GAME;
					}

				}

				if (end_loop)	break;
			}
		}
	}
	
	if (player == 1)
	{
		InitGame(initTh1(color), SINGLEP);
	}
	else if (player == 2)
	{
		InitGame(initTh1(DARK), MULTIP);
	}

	SDL_FreeSurface(StartS);
	SDL_DestroyWindow(StartW);
	StartW = NULL;
	StartS = NULL;
	return;
}
*/

void PlayGame();

void EndApp()
{
	if (GameSurface != NULL)		SDL_FreeSurface(GameSurface);
	if (GameWindow != NULL)
	{
		SDL_DestroyWindow(GameWindow);
	}
	SDL_Quit();
}

//utility function
void consoleoutputBoard(Board brd)
{
	cout << "\n\n";
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			cout <<(int) brd.grid[i][j].pcolor << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int SinglePlayerPlayGame();
int MultiPlayerPlayGame();

#ifdef TEST
bool TestUnmakeMove();
#endif

int main(int argc, char* argv[])
{
	//DO NOT REMOVE ------
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(time(0));
	//--------------------

	
#ifndef TEST
	//an instance of Start Screen
	StartScr AppStartScreen;
	AppStartScreen.Init();

	SDL_Color bgcolor = AppStartScreen.GetBgClr();

#endif

	//set initial appState
	appState = STARTSCR;

	int PlayerCount;
	int PlayerColour;

#ifdef DEBUG
	cout << sizeof(Board) << "\n";
	cout << sizeof(int8_t) << "\n";
#endif

#ifndef TEST
	//game loop
	while (appState != QUIT)
	{
		switch (appState)
		{
		case STARTSCR:
			appState = AppStartScreen.Run(PlayerCount, PlayerColour);
			AppStartScreen.CloseStartScr();
			if (appState == STARTGAME)
			{
				if (PlayerCount == 1)
					InitGame(initTh1(PlayerColour), SINGLEP);
				else
				{
					InitGame(initTh1(DARK), MULTIP);
				}
			}

			break;
		case STARTGAME:
			PlayGame();
			break;
		case QUIT:
			break;
		}
		if (appState == QUIT)
		{
			break;
		}
	}
#endif

	//DO NOT REMOVE-------------------------------------------

	//EXIT
#ifndef TEST
	AppStartScreen.Exit();
#endif
	
	EndApp();
	return 0;
}

/*
//should be obsolete
void startScr(SDL_Color bgclr)
{
	//colorKey
	SDL_Color clrKey;
	clrKey.r = 0x66;
	clrKey.g = 0xFF;
	clrKey.b = 0x11;

	StartW = SDL_CreateWindow("CHECKERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, STARTSCR_W, STARTSCR_H, SDL_WINDOW_SHOWN);
	StartS = SDL_GetWindowSurface(StartW);

	int i;
		SDL_FillRect(StartS, NULL, SDL_MapRGB(StartS->format, bgclr.r, bgclr.g, bgclr.b));


		//display

			//play button
			const int PlayB_H = 50;
			const int PlayB_W = 150;
			SDL_Surface* PlayS = SDL_LoadBMP("res\\PlayButton.bmp");
			SDL_Rect dR;
			dR.x = (STARTSCR_W - PlayB_W) / 2;
			dR.y = 35 + (STARTSCR_H - PlayB_H) / 2;
			dR.h = PlayB_H;
			dR.w = PlayB_W;
			SDL_BlitSurface(PlayS, NULL, StartS, &dR);




			//"checkers" text
			SDL_Surface* CheckersS = SDL_LoadBMP("res\\CheckersSS.bmp");
			SDL_SetColorKey(CheckersS, SDL_TRUE, SDL_MapRGB(CheckersS->format, clrKey.r, clrKey.g, clrKey.b));
			const int ChecH = 150;
			const int ChecW = 500;
			dR.x = (STARTSCR_W - ChecW) / 2;
			dR.y = -45 + (STARTSCR_H - ChecH) / 2;
			dR.h = PlayB_H;
			dR.w = PlayB_W;
			SDL_BlitSurface(CheckersS, NULL, StartS, &dR);


			SDL_UpdateWindowSurface(StartW);


			dR.x = (STARTSCR_W - PlayB_W) / 2;
			dR.y = 35 + (STARTSCR_H - PlayB_H) / 2;
			dR.h = PlayB_H;
			dR.w = PlayB_W;

		//event loop
		SDL_Event evt;
		bool quit = false;
		bool play = false;
		while (!quit)
		{
			while (SDL_PollEvent(&evt) != 0)
			{

				if (evt.type == SDL_QUIT || (evt.type==SDL_WINDOWEVENT && evt.window.type==SDL_WINDOWEVENT_CLOSE))
				{
					quit = true;
					appState = QUIT;
				}
				if (evt.type == SDL_MOUSEMOTION)
				{
					SDL_MouseMotionEvent evtmm = evt.motion;
					int x = evtmm.x;
					int y = evtmm.y;
					if (x > dR.x&& x<(dR.x + dR.w) && y>dR.y&& y < (dR.y + dR.h))
					{
						dR.x += 7;
						dR.y += 7;
						SDL_FillRect(StartS, &dR, SDL_MapRGBA(StartS->format, 0x55, 0x55, 0x55, 0x11));
						dR.x -= 7;
						dR.y -= 7;
						SDL_BlitSurface(PlayS, NULL, StartS, &dR);
						SDL_UpdateWindowSurface(StartW);
					}
					else
					{
						dR.x += 7;
						dR.y += 7;
						SDL_FillRect(StartS, &dR, SDL_MapRGB(StartS->format, bgclr.r, bgclr.g, bgclr.b));
						dR.x -= 7;
						dR.y -= 7;
						SDL_BlitSurface(PlayS, NULL, StartS, &dR);
						SDL_UpdateWindowSurface(StartW);
					}
				}
				if (evt.type == SDL_MOUSEBUTTONUP)
				{
					SDL_MouseButtonEvent evtbu = evt.button;
					int x = evtbu.x;
					int y = evtbu.y;
					if (x > dR.x&& x<(dR.x + dR.w) && y>dR.y&& y < (dR.y + dR.h))
					{
						play = true;
						quit = true;
						appState = CHOOSE_PLAYER;
					}
				}

				if (quit)	break;
				if (play)	break;
			}
		}

		SDL_FreeSurface(PlayS);
		SDL_FreeSurface(CheckersS);

		SDL_FreeSurface(StartS);
		SDL_DestroyWindow(StartW);
		StartW = NULL;
		StartS = NULL;

}



//singleplayer play game
//return -1 on dark wins, 0 on quit, 1 on light wins

*/

void PlayGame()
{
	//GameBoard = AIUtility::ConsoleBoardInput();
	SDL_ShowWindow(GameWindow);
	SDL_UpdateWindowSurface(GameWindow);
	SDL_Surface* winMsg = NULL;
	int ReturnState = -1;
	switch (GameMode)
	{
	case SINGLEP:
		ReturnState = SinglePlayerPlayGame();
		break;
	case MULTIP:
		ReturnState = MultiPlayerPlayGame();
		break;
	}
	switch (ReturnState)
	{
	case M_QUIT:
		appState = QUIT;
		break;
	case M_DARK_WINS:
		appState = STARTSCR;
		winMsg = SDL_LoadBMP("res\\dark_win.bmp");
		break;
	case M_LiGHT_WINS:
		appState = STARTSCR;
		winMsg = SDL_LoadBMP("res\\light_win.bmp");
		break;
	case M_DRAW:
		appState = STARTSCR;
		winMsg = SDL_LoadBMP("res\\draw.bmp");
		break;
	}
	if (winMsg != NULL)
	{
		SDL_BlitScaled(winMsg, NULL, GameSurface, NULL);
		SDL_UpdateWindowSurface(GameWindow);
		SDL_FreeSurface(winMsg);
		winMsg = NULL;

		SDL_Delay(5000);
	}


	SDL_FreeSurface(GameSurface);
	SDL_DestroyWindow(GameWindow);
	GameWindow = NULL;
	GameSurface = NULL;
	//appState = STARTSCR;
	//if (quit)	appState = QUIT;

}

int MultiPlayerPlayGame()
{
	SDL_Event e;
	int GameState = M_CONTINUE_GAME;
	while (GameState == M_CONTINUE_GAME)
	{
		if (GameState == M_CONTINUE_GAME)
		{
			switch (win())
			{
			case DARK:
				GameState = M_DARK_WINS;
				break;
			case LIGHT:
				GameState = M_LiGHT_WINS;
				break;
			case INT_MAX:
				GameState = M_DRAW;
				break;
			}
			if (GameState != M_CONTINUE_GAME)	break;
		}
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				std::cout << "SDL_QUIT event\n";
				GameState = M_QUIT;
				break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_CLOSE)
					GameState = M_QUIT;
				break;
			case SDL_MOUSEBUTTONUP:
				//std::cout << "Mouse Click\n";
				HandleMouseClick(e);
				SDL_UpdateWindowSurface(GameWindow);
				break;
			}
			if (GameState == M_QUIT)	break;
		}

		//check win
		if (GameState == M_CONTINUE_GAME)
		{
			switch (win())
			{
			case DARK:
				GameState = M_DARK_WINS;
				break;
			case LIGHT:
				GameState = M_LiGHT_WINS;
				break;
			case INT_MAX:
				GameState = M_DRAW;
				break;
			}
		}

	}

	return GameState;

}

int SinglePlayerPlayGame()
{
	int GameState = M_CONTINUE_GAME;
	SDL_Event e;
	turn = DARK;

	AIUtility::initAI();
	AI::init();

	//std::cout << "Human Player: " << GameSettings.player1<<"\n";
	//std::cout << "Turn:" << turn << "\n";

	//game loop
	while (GameState == M_CONTINUE_GAME)
	{
		if (GameState == M_CONTINUE_GAME)
		{
			switch (win())
			{
			case DARK:
				GameState = M_DARK_WINS;
				break;
			case LIGHT:
				GameState = M_LiGHT_WINS;
				break;
			case INT_MAX:
				GameState = M_DRAW;
				break;
			}
			if (GameState != M_CONTINUE_GAME)	break;
		}
		//
		//player turn
		if (turn == GameSettings.player1)
		{
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
					GameState = M_QUIT;
					break;

				case SDL_WINDOWEVENT:
					if (e.window.event == SDL_WINDOWEVENT_CLOSE)
						GameState = M_QUIT;
					break;
				case SDL_MOUSEBUTTONUP:
					//std::cout << "turn: " << turn << "\n";
					HandleMouseClick(e);
					SDL_UpdateWindowSurface(GameWindow);
					//std::cout << "turn: " << turn<<"\n";
					break;
				}
			}
		}
		else if (turn != GameSettings.player1)							//computer turn
		{

			//SDL_Delay(500);
			Move AIMove = GetAIMove(GameBoard, turn);
			GameBoard = Board::MakeMove(GameBoard, AIMove);
			//cout << "Making move of colour: " << turn << "\n";
			SDL_Surface* TempSurface = Board::CreateBoardSurface(GameBoard);
			SDL_BlitSurface(TempSurface, NULL, GameSurface, NULL);
			SDL_FreeSurface(TempSurface);
			SDL_UpdateWindowSurface(GameWindow);
			turn = GameSettings.player1;
			//std::cout << "turn: " << turn<<"\n";
#ifdef DEBUG
			std::cout << "Eval Red: " << AI::EvalPosition(GameBoard, DARK) << "\n";
			std::cout << "Positions Evaluated: " << AI::getMoveCount() << "\n";
			std::cout << "Projected Eval: " << AI::getProjectedEval() << "\n";
			cout << "\n";
#endif
		
		}

		//check win
		if (GameState == M_CONTINUE_GAME)
		{
			switch (win())
			{
			case DARK:
				GameState =M_DARK_WINS;
				break;
			case LIGHT:
				GameState = M_LiGHT_WINS;
				break;
			case INT_MAX:
				GameState = M_DRAW;
				break;
			}
		}

	}

	return GameState;
}

#ifdef TEST
bool TestUnmakeMove()
{
	
	SDL_ShowWindow(GameWindow);
	SDL_UpdateWindowSurface(GameWindow);
	cout << "\n\nEnter row and col:";
	int r, c;
	cin >> r >> c;
	cout << "inputted\n";
	std::vector<Move> moves = GetMovesPiece(GameBoard, GameBoard.grid[r][c], GET_ALL);
	if (moves.empty())	return false;
	Move move = moves[0];
	GameBoard = Board::MakeMove(GameBoard, move);
	cout << "made move\n";

	/*SDL_Surface* temp_Sur = Board::CreateBoardSurface(GameBoard);
	SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
	SDL_FreeSurface(temp_Sur);
	SDL_UpdateWindowSurface(GameWindow);*/
	cout << "rendered\n";

	consoleoutputBoard(GameBoard);

	SDL_Delay(2000);
	GameBoard = Board::UnMakeMove(GameBoard, move);
	cout << "un-made move\n";

	consoleoutputBoard(GameBoard);

	/*temp_Sur = Board::CreateBoardSurface(GameBoard);
	SDL_BlitSurface(temp_Sur, NULL, GameSurface, NULL);
	SDL_FreeSurface(temp_Sur);
	SDL_UpdateWindowSurface(GameWindow);*/
	cout << "rendered\n";
	SDL_Delay(2000);
	return true;
}
#endif