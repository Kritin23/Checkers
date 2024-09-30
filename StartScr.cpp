#include "StartScr.h"
#include <iostream>


int StartScr::Run(int& PlayerCount, int& PlayerColour)
{
	SDL_ShowWindow(SSWindow);
	bool quit = false;
	bool start = false;
	bool ShowGrayRect = false;
	PlayerColour = Null;
	PlayerCount = 0;
	SDL_Event e;
	int State = STARTSCR;
	int ReturnedState = 0;

	while (!quit)
	{
		ReturnedState = State;

		switch (State)
		{
		case QUIT:
			ReturnedState = QUIT;
			PlayerCount = 0;
			quit = true;
			break;
		case STARTSCR:
			RenderSS(ShowGrayRect);
			while (SDL_PollEvent(&e))
			{
				ReturnedState = OnEventSS(e, start, quit, ShowGrayRect);
				if (ReturnedState == QUIT || ReturnedState == CHOOSEPLAYER)	break;
				RenderSS(ShowGrayRect);
			}
			State = ReturnedState;
			quit = false;
			break;

		case CHOOSEPLAYER:
			RenderChoosePlayers();
			while (SDL_PollEvent(&e))
			{
				ReturnedState = OnEventChoosePlayers(e, PlayerCount);
				if (((QUIT | STARTSCR | STARTGAME | CHOOSECOLOR) & ReturnedState) != 0)	break;
				RenderChoosePlayers();
			}
			State = ReturnedState;
			quit = false;
			break;
		case CHOOSECOLOR:
			RenderChooseColour();
			while (SDL_PollEvent(&e))
			{
				ReturnedState = OnEventChooseColour(e, PlayerColour);
				if (((QUIT | CHOOSEPLAYER | STARTGAME) & ReturnedState) != 0)	break;
				RenderChooseColour();
				ReturnedState = CHOOSECOLOR;
			}
			State = ReturnedState;
			quit = false;
			
			break;

		case STARTGAME:
			quit = true;
			ReturnedState = STARTGAME;
		}
	}

	return ReturnedState;
}

int StartScr::OnEventSS(SDL_Event e, bool& start, bool& quit, bool& ShowGrayRect)
{
	int returnState = 0;
	SDL_Rect R = { 0,0,0,0 };
	switch (e.type)
	{
	case SDL_QUIT:
		returnState = QUIT;
		break;
	case SDL_MOUSEMOTION:
		R = { e.motion.x, e.motion.y, 1,1 };
		if (SDL_HasIntersection(&RectPlay, &R) == SDL_TRUE)	ShowGrayRect = true;
		else
		{
			ShowGrayRect = false;
		}
		returnState = STARTSCR;
		break;

	case SDL_MOUSEBUTTONUP:
		R = { e.motion.x, e.motion.y, 1,1 };
		returnState = STARTSCR;
		if (SDL_HasIntersection(&RectPlay, &R) == SDL_TRUE)
		{
			returnState = CHOOSEPLAYER;
		}
		break;
	default:
		returnState = STARTSCR;
	}
	return returnState;
}

void StartScr::RenderSS(bool RenderGrayRect)
{

	SDL_FillRect(SSSurface, NULL, SDL_MapRGB(SSSurface->format, BgClr.r, BgClr.g, BgClr.b));
	SDL_BlitSurface(TxtCheckers, NULL, SSSurface, &RectCheckers);

	if (RenderGrayRect)	SDL_FillRect(SSSurface, &GrayRect, SDL_MapRGB(SSSurface->format, 0x55, 0x55, 0x55));
	SDL_BlitSurface(TxtPlay, NULL, SSSurface, &RectPlay);

	SDL_UpdateWindowSurface(SSWindow);
}

int StartScr::OnEventChoosePlayers(SDL_Event e, int& PlayerCount)
{
	PlayerCount = 0;
	int returnState = CHOOSEPLAYER;
	switch (e.type)
	{
	case SDL_QUIT:
		returnState = QUIT;
		return returnState;
	case SDL_MOUSEBUTTONDOWN:
		SDL_Rect MouseClickRect = { 0, 0, 1, 1 };
		SDL_GetMouseState(&MouseClickRect.x, &MouseClickRect.y);

		//Single Player
		if (SDL_HasIntersection(&RectOnePlayer, &MouseClickRect) == SDL_TRUE)
		{
			returnState = CHOOSECOLOR;
			PlayerCount = 1;
			break;
		}

		//Two Player
		else if (SDL_HasIntersection(&RectTwoPlayer, &MouseClickRect)==SDL_TRUE)
		{
			returnState = STARTGAME;
			PlayerCount = 2;
			break;
		}

		//Back
		else if (SDL_HasIntersection(&RectBackButton, &MouseClickRect) == SDL_TRUE)
		{
			returnState = STARTSCR;
			PlayerCount = 0;
			break;
		}
		else
		{
			returnState = CHOOSEPLAYER;
			PlayerCount = 0;
			break;
		}
		break;

	}

	return returnState;
}

void StartScr::RenderChoosePlayers()
{
	SDL_FillRect(SSSurface, NULL, SDL_MapRGB(SSSurface->format, BgClr.r, BgClr.g, BgClr.b));
	SDL_BlitSurface(SurfaceOnePlayer, NULL, SSSurface, &RectOnePlayer);
	SDL_BlitSurface(SurfaceTwoPlayer, NULL, SSSurface, &RectTwoPlayer);
	SDL_BlitSurface(SurfaceBackButton, NULL, SSSurface, &RectBackButton);

	SDL_UpdateWindowSurface(SSWindow);
}

void StartScr::RenderChooseColour()
{
	SDL_FillRect(SSSurface, NULL, SDL_MapRGB(SSSurface->format, BgClr.r, BgClr.g,BgClr.b));

	SDL_BlitSurface(SurfaceBackButton, NULL, SSSurface, &RectBackButton);
	SDL_BlitSurface(SurfacePlayAs, NULL, SSSurface, &RectPlayAs);
	SDL_BlitSurface(SurfaceWhiteRed, &SrcWhite, SSSurface, &DstWhite);
	SDL_BlitSurface(SurfaceWhiteRed, &SrcRed, SSSurface, &DstRed);
	SDL_UpdateWindowSurface(SSWindow);
}

int StartScr::OnEventChooseColour(SDL_Event e, int& PlayerColor)
{
	PlayerColor = Null;
	int ReturnState = CHOOSECOLOR;
	switch (e.type)
	{
	case SDL_QUIT:
		ReturnState = QUIT;
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_Rect MouseClick = { 0,0,1,1 };
		SDL_GetMouseState(&MouseClick.x, &MouseClick.y);

		//back
		if (SDL_HasIntersection(&MouseClick, &RectBackButton) == SDL_TRUE)
		{
			ReturnState = CHOOSEPLAYER;
			break;
		}

		//red
		else if (SDL_HasIntersection(&MouseClick, &DstRed) == SDL_TRUE)
		{
			ReturnState = STARTGAME;
			PlayerColor = DARK;
			break;
		}

		//white
		else if (SDL_HasIntersection(&MouseClick, &DstWhite) == SDL_TRUE)
		{
			ReturnState = STARTGAME;
			PlayerColor = LIGHT;
			break;
		}
		else
		{
			PlayerColor = Null;
			ReturnState = CHOOSECOLOR;
		}
	}
	return ReturnState;
}

