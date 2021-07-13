#ifndef STATICGAMEOBJECT_H_
#define STATICGAMEOBJECT_H_
#include "GameObject.h"
class StaticGameObject : public GameObject
{
	protected:
		double worldX, worldY;
		double angle;

	public:
		StaticGameObject(SDL_Rect *r, SDL_Surface *s,double x, double y,double a);
		double getWorldX();
		double getWorldY();
		double getAngle();
		
		void setWorldX(double);
		void setWorldY(double);
		void rotate(double a);
		

};
#endif
