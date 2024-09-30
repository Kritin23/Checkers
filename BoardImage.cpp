#include "BoardImage.h"
#include <SDL.h>
#include <fstream>



SDL_Surface* CreateSDLSurface(int w,int h)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,0, 0,0,0);
	return surface;
}


SDL_Surface* boardImg::CreateboardImg(boardImg brdimg)
{
	SDL_Surface* fsurface=CreateSDLSurface(640,640);
	Uint32 clrB = SDL_MapRGB(fsurface->format, brdimg.clrBckg.r, brdimg.clrBckg.g, brdimg.clrBckg.b);
	Uint32 clrL = SDL_MapRGB(fsurface->format, brdimg.clrLight.r, brdimg.clrLight.g, brdimg.clrLight.b);
	Uint32 clrD = SDL_MapRGB(fsurface->format, brdimg.clrDark.r, brdimg.clrDark.g, brdimg.clrDark.b);

	SDL_FillRect(fsurface, NULL, clrB);
	SDL_Surface* grid = Creategrid(brdimg.clrDark, brdimg.clrLight);

	//create design
	SDL_Rect design;
	design.x = 32;
	design.y = 32;
	design.h = 576;
	design.w = 576;

	//outer-dark;
	SDL_FillRect(fsurface, &design, clrD);

	//line light 4px
	design.x += 20;
	design.y += 20;
	design.h -= 40;
	design.w -= 40;
	SDL_FillRect(fsurface, &design, clrL);

	//dark strip 8px
	design.x += 4;
	design.y += 4;
	design.h -= 8;
	design.w -= 8;
	SDL_FillRect(fsurface, &design, clrD);

	//black line 1px
	design.x += 7;
	design.y += 7;
	design.h -= 14;
	design.w -= 14;
	SDL_FillRect(fsurface, &design, SDL_MapRGB(fsurface->format,0,0,0));

	//board 512-512
	//line light 4px
	design.x += 1;
	design.y += 1;
	design.h -= 2;
	design.w -= 2;
	SDL_BlitSurface(grid, NULL, fsurface, &design);

	SDL_FreeSurface(grid);

	return fsurface;
}

SDL_Surface* boardImg::Creategrid(SDL_Color cdark, SDL_Color clight)
{
	SDL_Surface* thissurface=CreateSDLSurface(512,512);
	SDL_Rect tile;
	tile.x = 0;
	tile.y = 0;
	tile.h = 64;
	tile.w = 64;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Uint32 actcolor;
			if (((i + j) % 2) == 0)	actcolor = SDL_MapRGB(thissurface->format, clight.r, clight.g, clight.b);
			else
			{
				actcolor = SDL_MapRGB(thissurface->format, cdark.r, cdark.g, cdark.b);
			}
			SDL_FillRect(thissurface, &tile, actcolor);
			tile.x += 64;
		}
		tile.x = 0;
		tile.y += 64;

	}
	return thissurface;
}
