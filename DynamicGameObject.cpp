#include "DynamicGameObject.h"
#include <iostream>
#include <cmath>
DynamicGameObject::DynamicGameObject(SDL_Rect *r,SDL_Surface *s,double x, double y, double a,double sp):StaticGameObject(r,s,x,y,a)
{
	speed = sp;
	calcRealSpeeds();
}

int DynamicGameObject::move()
{
	worldX+=speedX;
	worldY+=speedY;
	
	return 0;
}

double DynamicGameObject::getSpeedX()
{
	return speedX;
}
double DynamicGameObject::getSpeedY()
{
	return speedY;
}

double DynamicGameObject::getSpeed()
{
	return speed;
}

void DynamicGameObject::calcRealSpeeds()
{
	speedX = speed*cos((angle-90)/180*M_PI);
	speedY = speed*sin((angle-90)/180*M_PI);
	//std::cout<<"dyn: "<<speed<<" "<<angle<<" "<<speedX<<" "<<speedY<<std::endl;
}

void DynamicGameObject::setSpeed(double sp)
{
	//std::cout<<"dyn:setSpeed\n";
	speed = sp;
	calcRealSpeeds();
	//std::cout<<speed<<" "<<angle<<" "<<speedX<<" "<<speedY<<std::endl;
}

void DynamicGameObject::rotate(double a)
{
	StaticGameObject::rotate(a);
	calcRealSpeeds();
}

int DynamicGameObject::getHealth()
{
	return health;
}
int DynamicGameObject::getDamage()
{
	return damage;
}

void DynamicGameObject::setHealth(int h)
{
	health = h;
}


void DynamicGameObject::setDamage(int d)
{
	damage = d;
}
