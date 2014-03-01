#ifndef GMMINIMAP_H
#define GMMINIMAP_H

#include "render.hpp"
#include "gmmapmaker.hpp"

//Function to produce a minimap surface given the current map.
SDL_Surface* get_minimap()
{
	float scaleFactor = (1.0/((40.0 * (MAP_W+1)) / 160.0));
	int heightOverlapping = (20*scaleFactor)/2+1;
	int yOffset = (40*scaleFactor)-(20*scaleFactor);
	SDL_Surface* newMinimap = SDL_CreateRGBSurface(0, 160, 120, 32, 0, 0, 0, 0);
	SDL_Surface* miniTile = NULL;
	for(int x=0; x<MAP_W; x++){for(int y=0; y<MAP_H; y++){
		miniTile = rotozoomSurface(currentMap.tile[y][x].image, 0, scaleFactor, 0);
		apply(x*(40*scaleFactor)+(y%2!=0)*(20*scaleFactor), y*heightOverlapping-yOffset, miniTile, newMinimap);
	}}
	SDL_FreeSurface(miniTile);
	return newMinimap;
}

int draw_minimap()
{
	float scaleFactor = (1.0/((40.0 * (MAP_W+1)) / 160.0));
	apply(0,0,get_minimap(),screen);
	rectangleRGBA(screen, cameraX*scaleFactor,cameraY*scaleFactor, 
					(160 > SCREEN_W*scaleFactor 	? SCREEN_W*scaleFactor	: 160)+cameraX*scaleFactor,
					(120 > SCREEN_H*scaleFactor 	? SCREEN_H*scaleFactor	: 120)+cameraY*scaleFactor,
					0xFF, 0xFF, 0xFF, 0xFF);
	return 0;
}

#endif
