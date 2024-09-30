#pragma once
#include <SDL.h>


#define	TILE_D	64
#define BOARD_BEGIN_C 64
#define BOARD_SURFACE_D 640

class boardImg
{
public:
	SDL_Color clrLight;
	SDL_Color clrDark;
	SDL_Color clrBckg;

	static SDL_Surface* CreateboardImg(boardImg brdimg);		//board from class
	
	/**
		@brief creates checkered grid from colors
		@param cdark - Dark Color 
		@param clight - Light Color
		@return SDL_Surface* containing grid
	*/
	static SDL_Surface* Creategrid(SDL_Color cdark,SDL_Color clight);

};

/**
create SDL_Surface with given height and width
*/
SDL_Surface* CreateSDLSurface(int w,int h);

