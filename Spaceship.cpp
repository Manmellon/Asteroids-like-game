#include "Spaceship.h"

#include <cstdio>
#include <cmath>
Spaceship::Spaceship(SDL_Rect *r, SDL_Surface *s,double x,double y, double a,double sp,SDL_Color *c=NULL):
DynamicGameObject(r,s,x,y,a,sp)
{
	health = 500*rect->h;
	damage = 1*rect->h;
	if (c==NULL)
	{
		color = new SDL_Color;
		color->r=color->g=color->b = 127;
		color->a=255;
	}
	else
	{
		color = c;
	}
	SDL_Surface *color_mask = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(color_mask, NULL, (color->a << 24) + (color->r << 16) +
         (color->g << 8)  + color->b);
    SDL_SetSurfaceBlendMode(color_mask,SDL_BLENDMODE_MOD);
    SDL_BlitSurface(color_mask, NULL, surface, NULL);
}

int Spaceship::getLife()
{
	return life;
}
int Spaceship::getEnergy()
{
	return energy;
}
int Spaceship::getSpeed()
{
	return speed;
}

Laser* Spaceship::shootLaser()
{
	Laser *laser = new Laser((worldX+rect->w/2)+0.75*rect->w*cos((angle-90)/180*M_PI),
							(worldY+rect->h/2)+0.75*rect->h*sin((angle-90)/180*M_PI),angle);
	return laser;
}
