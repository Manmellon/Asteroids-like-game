#include "Laser.h"
#include <cstdio>
Laser::Laser(double x, double y, double a):DynamicGameObject(NULL,NULL,x,y,a,10)
{
	health = 100000;
	damage = 1000;
	//puts("start laser construct");
	surface = SDL_CreateRGBSurface(0, 1, 5, 32, 0, 0, 0, 0);
	
	rect = new SDL_Rect;
	rect->x = rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	
	SDL_FillRect(surface,NULL,0xFFFFFFFF);
	
	way = 0;
	//puts("end laser construct");
}

int Laser::move()
{
	DynamicGameObject::move();
	way += 1;
	//printf("%lf\n",way);
	if (way>40) return -1;
	else return 0;
}
