#include "GameParty.h"
#include <stdio.h>

GameParty::GameParty(SDL_Renderer *renderer, SDL_Rect *camera_rect)
{
	world = new GameWorld(1000, 1000, renderer);
	camera = new Camera(camera_rect, NULL,0, 0);
	points = 0;
}

GameParty::~GameParty()
{
	delete world;
	delete camera;
}

void GameParty::loadGame()
{
	FILE *f = fopen("save.dat","rb");

	fread(&points,sizeof(int),1,f);
	/*int h;
	fread(&h,sizeof(int),1,f);
	world->getMyShip()->setHealth(h);
	*/
	DynamicGameObject *obj;
	double x,y,a,sp,he,h;
	int itmp;
	size_t size;
	fread(&size,sizeof(size_t),1,f);
	for (size_t i=0;i<size;i++)
	{
		fread(&itmp,sizeof(int),1,f);
		world->getTypes()->push_back(itmp);
		
		fread(&x,sizeof(double),1,f);
		fread(&y,sizeof(double),1,f);
		fread(&a,sizeof(double),1,f);
		fread(&sp,sizeof(double),1,f);
		fread(&he,sizeof(double),1,f);
		fread(&h,sizeof(double),1,f);
		
	}
	fclose(f);
}

void GameParty::saveGame()
{
	FILE *f = fopen("save.dat","wb");
	fwrite(&points,sizeof(int),1,f);
	/*int h = world->getMyShip()->getHealth();
	fwrite(&h,sizeof(int),1,f);
	*/
	double tmp;
	int itmp;
	
	size_t size = world->getObjectsList()->size();
	fwrite(&size,sizeof(size_t),1,f);
	for (size_t i=0;i<size;i++)
	{

		itmp = (*world->getTypes())[i];
		fwrite(&itmp,sizeof(int),1,f);
		tmp = (*world->getObjectsList())[i]->getWorldX();
		fwrite(&tmp,sizeof(double),1,f);
		tmp = (*world->getObjectsList())[i]->getWorldY();
		fwrite(&tmp,sizeof(double),1,f);
		tmp = (*world->getObjectsList())[i]->getAngle();
		fwrite(&tmp,sizeof(double),1,f);
		tmp = (*world->getObjectsList())[i]->getSpeed();
		fwrite(&tmp,sizeof(double),1,f);
		tmp = (*world->getObjectsList())[i]->getHealth();
		fwrite(&tmp,sizeof(double),1,f);
		tmp = (*world->getObjectsList())[i]->getRect()->h;
		fwrite(&tmp,sizeof(double),1,f);
	}
	
	
	fclose(f);
}

GameWorld* GameParty::getWorld()
{
	return world;
}

Camera* GameParty::getCamera()
{
	return camera;
}

int GameParty::getPoints()
{
	return points;
}

void GameParty::setPoints(int p)
{
	points = p;
}
