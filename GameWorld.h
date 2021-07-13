#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "DynamicGameObject.h"

#include <vector>
using namespace std;
class GameWorld : public GameObject
{
	protected:
	int width, height;
	vector<DynamicGameObject*> objectsList;
	DynamicGameObject* myShip;
	vector<int> types;
	SDL_Surface *images[2];
	public:
	GameWorld(int w,int h, SDL_Renderer *renderer);
	int getWidth();
	int getHeight();
	int update();
	vector<DynamicGameObject*>* getObjectsList();
	vector<int>* getTypes();
	DynamicGameObject* getMyShip();
	
};
#endif
