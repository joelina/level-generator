#ifndef GMOBJECT_H
#define GMOBJECT_H

#include "render.hpp"

class gmObject
{
	private:
	public:
	int x, y;
	SDL_Surface* image = NULL;
	bool mouse_is_over()
	{
		//If the mouse is over the object, return true, otherwise, return false.
		return(mouseX > x &&
		mouseX < x+image->w &&
		mouseY > y &&
		mouseY < y+image->h);
	}
};

#endif
