#include "Asteroid.h"

Asteroid::Asteroid(SDL_Rect *r, SDL_Surface *s,double x, double y, double a,double sp):DynamicGameObject(r,s,x,y,a,sp)
{
	health = 100*rect->w;
	damage = 10*rect->w;
}
