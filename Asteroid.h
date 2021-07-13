#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "DynamicGameObject.h"


class Asteroid : public DynamicGameObject
{
	public:
	Asteroid(SDL_Rect *r, SDL_Surface *s,double x,double y,double a,double sp);

};
#endif
