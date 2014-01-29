#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <iostream>
#include <ctime>

SDL_Surface* screen;
int cameraX, cameraY;
SDL_Event event;
bool running = true;
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
int map[40][40];

void get_map()
{
	void* mapPointer = malloc(sizeof(int));
	for(int x = 0; x < 40; x++)
	{
		for(int y = 0; y < 40; y++)
		{
			int* mapData = (int*)mapPointer+x+y;
			map[y][x] = *mapData ^ (time(NULL)+x+y);
			//free(mapPointer);
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
	for(int x = 0; x < 40; x++)
	{
		for(int y = 0; y < 40; y++)
		{
			int heightOverlapping = (21)/2+1;
			int yOffset = 40-21;
				 if(map[y][x]%2 == 0){tile = load_image("tile/sand.png");}
			else if(map[y][x]%3 == 0){tile = load_image("tile/gravel.png" );}
			else if(map[y][x]%4 == 0){tile = load_image("tile/ocean.png" );}
			else if(map[y][x]%5 == 0){tile = load_image("tile/rock.png" );}
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
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_q){get_map(); render_tiles();}
				if(event.key.keysym.sym == SDLK_p){running = false;}
			}
		}
		SDL_Flip(screen);
	}
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
