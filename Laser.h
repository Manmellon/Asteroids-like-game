#ifndef LASER_H_
#define LASER_H_
#include "DynamicGameObject.h"

class Laser : public DynamicGameObject
{
	protected:
		double way;
	public:
	Laser(double x, double y,double a);
	int move();

};
#endif
