#ifndef GMGRIDCURSOR_H
#define GMGRIDCURSOR_H

#include "render.hpp"
#include "gmmapmaker.hpp"

//Retrieves the tile the mouse is hovering over.
gmTile* get_hovering_tile()
{
	SDL_Surface* mouseMap 		= load_image("mousemap.png");
	int regionX 				= (mouseX+cameraX)/40;
	int regionY 				= 2*((mouseY+cameraY)/21);
	int mouseMapX 				= (mouseX+cameraX)%40;
	int mouseMapY 				= (mouseY+cameraY)%21;
	Uint32 colour = get_pixel32(mouseMap, mouseMapX, mouseMapY);
	int regionDx, regionDy;
	//Red.
	if(colour == SDL_MapRGB(mouseMap->format, 255, 0, 0))
	{
		regionDx = -1;
		regionDy = -1;
	}
	//Yellow.
	if(colour == SDL_MapRGB(mouseMap->format, 255, 255, 0))
	{
		regionDx = 0;
		regionDy = -1;
	}
	//White.
	if(colour == SDL_MapRGB(mouseMap->format, 255, 255, 255))
	{
		regionDx = 0;
		regionDy = 0;
	}
	//Green.
	if(colour == SDL_MapRGB(mouseMap->format, 0, 255, 0))
	{
		regionDx = -1;
		regionDy = 1;
	}
	//Blue.
	if(colour == SDL_MapRGB(mouseMap->format, 0, 0, 255))
	{
		regionDx = 0;
		regionDy = 1;
	}
	return &currentMap.tile[regionY+regionDy][regionX+regionDx];
}

#endif
