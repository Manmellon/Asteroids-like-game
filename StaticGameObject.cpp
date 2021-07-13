#include "StaticGameObject.h"

StaticGameObject::StaticGameObject(SDL_Rect *r, SDL_Surface *s,double x,double y,double a):GameObject(r,s)
{
	worldX = x;
	worldY = y;
	angle = a;
	
	//collisionRadius = (rect->w + rect->h)/2/2;
}

double StaticGameObject::getWorldX()
{
	return worldX;
}
double StaticGameObject::getWorldY()
{
	return worldY;
}

double StaticGameObject::getAngle()
{
	return angle;
}


void StaticGameObject::setWorldX(double x)
{
	worldX = x;
}

void StaticGameObject::setWorldY(double y)
{
	worldY = y;
}

void StaticGameObject::rotate(double a)
{
	angle += a;
}
