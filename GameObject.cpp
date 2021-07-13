#include "GameObject.h"
GameObject::GameObject(SDL_Rect *r, /*SDL_Texture *t*/SDL_Surface *s)
{
	rect = r;
	//texture = t;
	surface = s;
}

GameObject::~GameObject()
{
	SDL_FreeSurface(surface);
	//free(rect);
}

SDL_Rect* GameObject::getRect()
{
	return rect;
}

/*SDL_Texture* GameObject::getTexture()
{
	return texture;
}*/

SDL_Surface* GameObject::getSurface()
{
	return surface;
}
