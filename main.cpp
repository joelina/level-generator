#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <iostream>

SDL_Surface* screen;
int cameraX, cameraY;
/*
int map[10][10] = {
					{0,1,1,0,1,1,0,1,1,2},
					{0,0,0,0,0,0,0,1,0,1},
					{0,0,1,0,0,1,0,0,1,0},
					{0,1,1,0,1,1,0,1,1,0},
					{0,0,0,0,0,0,0,0,0,1},
					{0,0,1,0,0,1,0,0,1,0},
					{0,1,1,0,1,1,0,1,1,0},
					{0,0,0,0,0,0,0,0,0,1},
					{0,0,1,0,0,1,0,0,1,0},
					{0,0,1,0,0,1,0,0,1,0}
				};
*/
int map[10][10];

void get_map()
{
	for(int x = 0; x < 10; x++)
	{
		for(int y = 0; y < 10; y++)
		{
			void* mapPointer = malloc(sizeof(int));
			int* mapData = (int*)mapPointer;
			map[y][x] = *mapData;
		}
	}
	return;
}

bool is_odd(int x){if (x%2 == 0){return true;} else return false;}

SDL_Surface* load_image(std::string filename)
{
	//Load an image file.
	SDL_Surface* loadedImage = IMG_Load(filename.c_str());
	SDL_Surface* optimisedImage = NULL;
	//If there was NO problem loading the image file.
	if (loadedImage != NULL)
	{
		optimisedImage = SDL_DisplayFormat(loadedImage);
		//Set colour key, which is cyan.
		Uint32 colourkey = SDL_MapRGB(optimisedImage->format, 0, 0xFF, 0xFF);
		SDL_SetColorKey(optimisedImage, SDL_SRCCOLORKEY, colourkey);
	}
	//If there WAS a problem loading the image file.
	else
	{
		std::cout << "Error: Unable to load image - " << SDL_GetError();
		return NULL;
	}
	//Free up memory allocated to the original, loaded image.
	SDL_FreeSurface(loadedImage);
	return optimisedImage;
}

void apply(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip = NULL){
	if (source != NULL)
	{
		SDL_Rect offset;
		offset.x = x;
		offset.y = y;
		SDL_BlitSurface(source, clip, dest, &offset);
	}
	else{std::cout << "Error: source is NULL.";}
	return;
}

void render_tiles()
{
	SDL_Surface* tile = NULL;
	for(int x = 0; x < 10; x++)
	{
		for(int y = 0; y < 10; y++)
		{
			int heightOverlapping = (21)/2+1;
			int yOffset = 40-21;
				 if(map[y][x]%15 <= 2){tile = load_image("tile/sand.png");}
			else if(map[y][x]%9 <= 2){tile = load_image("tile/rock.png" );}
			else 				   	 {tile = load_image("tile/grass.png");}
			apply(x*40+(is_odd(y))*20, y*heightOverlapping-yOffset, tile, screen);
		}
	}
	return;
}

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	SDL_Delay(2000);
	return;
}

void run()
{
	get_map();
	render_tiles();
	return;
}

void halt()
{
	SDL_Flip(screen);
	SDL_Delay(2000);
	return;
}

int main()
{
	init();
	run();
	halt();
	return 0;
}
