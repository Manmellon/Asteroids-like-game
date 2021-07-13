#ifndef DYNAMICGAMEOBJECT_H_
#define DYNAMICGAMEOBJECT_H_
#include "StaticGameObject.h"
class DynamicGameObject : public StaticGameObject
{
	protected:
	double speedX, speedY;
	double speed;
	
	int damage, health;
	
	public:
	DynamicGameObject(SDL_Rect *r, SDL_Surface *s,double x,double y,double a, double sp);
	virtual int move();
	double getSpeedX();
	double getSpeedY();
	double getSpeed();
	void calcRealSpeeds();
	void setSpeed(double sp);
	void rotate(double a);
	
	int getDamage();
	int getHealth();
	
	void setDamage(int);
	void setHealth(int);
};
#endif
