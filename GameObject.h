#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <SDL2\SDL.h>
class GameObject
{
	protected:
		SDL_Rect *rect;
		SDL_Surface *surface;
	public:
		GameObject(SDL_Rect *r, SDL_Surface *s);
		~GameObject();
		SDL_Rect* getRect();
		SDL_Surface* getSurface();
};
#endif
