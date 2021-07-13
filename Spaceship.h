#ifndef SPACESHIP_H_
#define SPACESHIP_H_
#include "DynamicGameObject.h"
#include "Laser.h"
class Spaceship : public DynamicGameObject
{
	protected:

	SDL_Color *color;
	
	int attack_points;
	int defense_points;
	int speed_points;
	int points;
	
	int life;
	int energy;
	int speed;
	
	
	public:
	Spaceship(SDL_Rect *r, SDL_Surface *s,double x,double y, double a,double sp, SDL_Color *c);
	void rotate(int dir);
	void setSpeed(int sp);
	
	int getLife();
	int getEnergy();
	int getSpeed();
	
	Laser* shootLaser();
};
#endif
