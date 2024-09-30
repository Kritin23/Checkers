#pragma once

#include <SDL.h>
#include <cstdlib>
#include "plot.h"

#define STARTSCR_H 480
#define STARTSCR_W 640

enum RunState
{
	QUIT = 1,
	STARTSCR = 2,
	CHOOSEPLAYER = 4,
	CHOOSECOLOR = 8,
	STARTGAME = 16
};

class StartScr
{
private:
	SDL_Color		ClrKey;
	SDL_Color		BgClr;
	SDL_Window*		SSWindow;
	SDL_Surface*	SSSurface;

	//Start Screen
	SDL_Surface*	TxtCheckers;
	SDL_Rect		RectCheckers;
	SDL_Surface*	TxtPlay;
	SDL_Rect		RectPlay;
	SDL_Rect		GrayRect;

	//Choose No. of Players
	SDL_Rect RectOnePlayer;
	SDL_Rect RectTwoPlayer;
	SDL_Rect RectBackButton;
	SDL_Surface* SurfaceOnePlayer;
	SDL_Surface* SurfaceTwoPlayer;
	SDL_Surface* SurfaceBackButton;

	//Choose Color
	SDL_Rect RectPlayAs;
	SDL_Rect SrcWhite;
	SDL_Rect DstWhite;
	SDL_Rect SrcRed;
	SDL_Rect DstRed;
	SDL_Surface* SurfacePlayAs;
	SDL_Surface* SurfaceWhiteRed;



public:

	//default constructor
	StartScr()
	{
		ClrKey	= { 0,0,0 };
		BgClr	= { 0,0,0 };
		SSWindow	= NULL;
		SSSurface	= NULL;
		TxtCheckers	= NULL;
		TxtPlay		= NULL;
		GrayRect		= { 0,0,0,0 };
		RectOnePlayer	= { 0,0,0,0 };
		RectTwoPlayer	= { 0,0,0,0 };
		RectBackButton	= { 0,0,0,0 };
		SurfaceOnePlayer  = NULL;
		SurfaceTwoPlayer  = NULL;
		SurfaceBackButton = NULL;

	};

	//function to initialize start screen
	void Init()
	{
		ClrKey = { 0x66,0xFF,0x11 };
		BgClr = { Uint8(rand() % 255), Uint8(rand() % 255), Uint8(rand() % 255) };
		SSWindow = SDL_CreateWindow("CHECKERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, STARTSCR_W, STARTSCR_H, SDL_WINDOW_SHOWN);
		SSSurface = SDL_GetWindowSurface(SSWindow);

		//load media
		//checkers
		TxtCheckers = SDL_LoadBMP("res\\CheckersSS.bmp");
		SDL_SetColorKey(TxtCheckers, SDL_TRUE, SDL_MapRGB(TxtCheckers->format, ClrKey.r, ClrKey.g, ClrKey.b));
		const int ChecH = 150;
		const int ChecW = 500;
		RectCheckers.x = (STARTSCR_W - ChecW) / 2;
		RectCheckers.y = -45 + (STARTSCR_H - ChecH) / 2;
		RectCheckers.h = ChecH;
		RectCheckers.w = ChecW;


		//play
		TxtPlay = SDL_LoadBMP("res\\PlayButton.bmp");
		const int PlayB_H = 50;
		const int PlayB_W = 150;
		RectPlay.x = (STARTSCR_W - PlayB_W) / 2;
		RectPlay.y = 35 + (STARTSCR_H - PlayB_H) / 2;
		RectPlay.h = PlayB_H;
		RectPlay.w = PlayB_W;

		//GrayRect
		GrayRect = RectPlay;
		GrayRect.x += 7;
		GrayRect.y += 7;


		//Choose no. of Players
		const int PLAYERS_H = 150;
		const int PLAYERS_W = 300;
		const int k = -2;
		const int y = 50;

		//OnePlayer
		RectOnePlayer.x = (STARTSCR_W / 2) - k - PLAYERS_W;
		RectOnePlayer.y = y;
		RectOnePlayer.h = PLAYERS_H;
		RectOnePlayer.w = PLAYERS_W;
		SurfaceOnePlayer = SDL_LoadBMP("res\\OPlayer.bmp");
		SDL_SetColorKey(SurfaceOnePlayer, SDL_TRUE, SDL_MapRGB(SurfaceOnePlayer->format, ClrKey.r, ClrKey.g, ClrKey.b));

		//TwoPlayer
		RectTwoPlayer.x = (STARTSCR_W / 2) + k;
		RectTwoPlayer.y = y;
		RectTwoPlayer.h = PLAYERS_H;
		RectTwoPlayer.w = PLAYERS_W;
		SurfaceTwoPlayer = SDL_LoadBMP("res\\TPlayer.bmp");
		SDL_SetColorKey(SurfaceTwoPlayer, SDL_TRUE, SDL_MapRGB(SurfaceTwoPlayer->format, ClrKey.r, ClrKey.g, ClrKey.b));

		//Back Button
		RectBackButton.x = 5;
		RectBackButton.y = 5;
		RectBackButton.h = 50;
		RectBackButton.w = 50;
		SurfaceBackButton = SDL_LoadBMP("res\\back.bmp");
		SDL_SetColorKey(SurfaceBackButton, SDL_TRUE, SDL_MapRGB(SurfaceBackButton->format, ClrKey.r, ClrKey.g, ClrKey.b));


		//Choose Color

		//PLAY AS...
		SurfacePlayAs = SDL_LoadBMP("res\\Player12.bmp");
		SDL_SetColorKey(SurfacePlayAs, SDL_TRUE, SDL_MapRGB(SurfacePlayAs->format, ClrKey.r, ClrKey.g, ClrKey.b));
		RectPlayAs.x = 10;
		RectPlayAs.y = 70;
		RectPlayAs.h = 50;
		RectPlayAs.w = 260;

		//White / Red
		SurfaceWhiteRed = SDL_LoadBMP("res\\BW.bmp");
		
		//white
		SrcWhite.x = 0;
		SrcWhite.y = 0;
		SrcWhite.h = 50;
		SrcWhite.w = 150;

		DstWhite.x = 20;
		DstWhite.y = 200;
		DstWhite.h = 50;
		DstWhite.w = 150;

		//Red
		SrcRed.x = 150;
		SrcRed.y = 0;
		SrcRed.h = 50;
		SrcRed.w = 150;

		DstRed.x = 200;
		DstRed.y = 200;
		DstRed.h = 50;
		DstRed.w = 150;
	};

	//function to run start screen
	//return appState as defined in enum RunState
	int Run(int &PlayerCount, int& PlayerColour);


	int OnEventSS(SDL_Event e, bool& start, bool& quit, bool& ShowGrayRect);
	void RenderSS(bool RenderGrayRect);

	int OnEventChoosePlayers(SDL_Event e, int &PlayerCount);
	void RenderChoosePlayers();

	int OnEventChooseColour(SDL_Event e, int& PlayerColour);
	void RenderChooseColour();

	

	//function to destroy window and surface
	void Exit()
	{
		ClrKey = { 0,0,0 };
		BgClr = { 0,0,0 };
		SDL_DestroyWindow(SSWindow);
		SDL_FreeSurface(SSSurface);
		SSWindow = NULL;
		SSSurface = NULL;
		SDL_FreeSurface(SurfaceBackButton);
		SDL_FreeSurface(SurfaceOnePlayer);
		SDL_FreeSurface(SurfacePlayAs);
		SDL_FreeSurface(SurfaceTwoPlayer);
		SDL_FreeSurface(SurfaceWhiteRed);
		SDL_FreeSurface(TxtCheckers);
		SDL_FreeSurface(TxtPlay);
	};

	void CloseStartScr()
	{
		SDL_HideWindow(SSWindow);
	}

	SDL_Color GetBgClr()
	{
		return BgClr;
	};


};
