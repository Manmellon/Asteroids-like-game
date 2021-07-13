#include "GameWorld.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Laser.h"

#include <SDL2/SDL_Image.h>

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstdio>
GameWorld::GameWorld(int w, int h, SDL_Renderer *renderer):GameObject(NULL,NULL)
{
	width = w;
	height = h;
	int s = width*height;
	DynamicGameObject *obj;
	//SDL_Texture *tmp_texture;
	//SDL_Surface *loaded_image;
	SDL_Surface *tmp_surface;
	double x,y,a;
	double sp;
	SDL_Rect *tmp_rect;
	
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_Renderer *worldRenderer = SDL_CreateSoftwareRenderer(surface);
	
	SDL_SetRenderDrawColor(worldRenderer, 0, 0, 0xFF, 0);
	
	for (int i=0;i*40<=width;i++)
	{
		SDL_RenderDrawLine(worldRenderer, i*40,0,i*40,height);
	}
	
	for (int i=0;i*40<=height;i++)
	{
		SDL_RenderDrawLine(worldRenderer, 0,i*40,width,i*40);
	}
	
	srand(time(NULL));
	
	//loaded_image = IMG_Load("asteroid.png");
	images[0] = IMG_Load("asteroid.png");
	for (int i=0;i<s/50000;i++)
	{
		int size = 20+rand()%80;
		
		tmp_surface = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);
		SDL_SetSurfaceBlendMode(tmp_surface,SDL_BLENDMODE_ADD);

		
		//SDL_BlitScaled(loaded_image, NULL, tmp_surface, NULL);
		SDL_BlitScaled(images[0], NULL, tmp_surface, NULL);
		
		
		tmp_rect = new SDL_Rect();
		tmp_rect->x = tmp_rect->y = 0;
		tmp_rect->w = tmp_surface->w;
		tmp_rect->h = tmp_surface->h;
		
		x = rand()%(width-size);
		y = rand()%(height-size);
		sp = -3+6.*rand()/RAND_MAX;

		a = 360.*rand()/RAND_MAX;
		//printf("%lf\n",a);
		obj = new Asteroid(tmp_rect,tmp_surface,x,y,a,sp);

		objectsList.push_back(obj);
		types.push_back(0);
	}
	
	//SDL_FreeSurface(loaded_image);
	//loaded_image = IMG_Load("spaceship.png");
	images[1] = IMG_Load("spaceship.png");
	
	SDL_Color *myColor = new SDL_Color;
	myColor->r = myColor->b = 0;
	myColor->g = 0xFF;
	
	for (int i=0;i<s/100000;i++)
	{
		int size = 20+rand()%40;
		if (i==0) size = 30;
		//double k = (double)loaded_image->w/loaded_image->h;
		double k = (double)images[1]->w/images[1]->h;
		
		tmp_surface = SDL_CreateRGBSurface(0, k*size, size, 32, 0, 0, 0, 0);
		SDL_SetSurfaceBlendMode(tmp_surface,SDL_BLENDMODE_ADD);

		
		//SDL_BlitScaled(loaded_image, NULL, tmp_surface, NULL);
		SDL_BlitScaled(images[1], NULL, tmp_surface, NULL);
		
		
		tmp_rect = new SDL_Rect();
		tmp_rect->x = tmp_rect->y = 0;
		tmp_rect->w = tmp_surface->w;
		tmp_rect->h = tmp_surface->h;
		
		x = rand()%(width-size);
		y = rand()%(height-size);
		a = 360.*rand()/RAND_MAX;
		
		sp = -1 + rand()%6;
		if (i==0) sp = 0;
		
		if (i==0)
		{
			obj = new Spaceship(tmp_rect,tmp_surface,x,y,a,sp,myColor);
		}
		else
		{
			obj = new Spaceship(tmp_rect,tmp_surface,x,y,a,sp,NULL);
		}
		objectsList.push_back(obj);
		types.push_back(1);
		if (i==0) myShip = obj;
		

	}
	
}

int GameWorld::update()
{
	SDL_Surface *tmp_surface;
	DynamicGameObject *obj;
	double x,y,a;
	double sp;
	SDL_Rect *tmp_rect;
	int points = 0;
	for (size_t i=0;i<objectsList.size();i++)
	{

		if (objectsList[i]->move()==-1)
		{
			//puts("DELETED");
			delete objectsList[i];
			objectsList.erase(objectsList.begin()+i);
			types.erase(types.begin()+i);
			
			i--;
			continue;
		}
		
		
		
		if (objectsList[i]->getWorldX()+objectsList[i]->getRect()->w<0)
		{
			objectsList[i]->setWorldX(width-objectsList[i]->getRect()->w);
		}
		else if (objectsList[i]->getWorldX()>width)
		{
			objectsList[i]->setWorldX(0-objectsList[i]->getRect()->w);
		}
		
		if (objectsList[i]->getWorldY()+objectsList[i]->getRect()->h<0)
		{
			objectsList[i]->setWorldY(height-objectsList[i]->getRect()->h);
		}
		else if (objectsList[i]->getWorldY()>height)
		{
			objectsList[i]->setWorldY(0-objectsList[i]->getRect()->h);
		}
		
		if (types[i]==1&&objectsList[i]!=getMyShip())
		{	
			int tmp = rand()%100;
			if (tmp<20)
			{
				Laser *tmp_laser = ((Spaceship*)objectsList[i])->shootLaser();
				objectsList.push_back(tmp_laser);
				types.push_back(2);
			}
		}
		
	}
	
	
	for (size_t i=0;i<objectsList.size();i++)
	{
		for (size_t j=0;j<objectsList.size();j++)
		{
			if (i==j) continue;
			double dist_x = objectsList[i]->getWorldX()+objectsList[i]->getRect()->w/2 - 
				(objectsList[j]->getWorldX()+objectsList[j]->getRect()->w/2);
			double dist_y = objectsList[i]->getWorldY()+objectsList[i]->getRect()->h/2 - 
				(objectsList[j]->getWorldY()+objectsList[j]->getRect()->h/2);
			
			dist_x = fabs(dist_x);
			dist_y = fabs(dist_y);
			
			//double dist=sqrt(dist_x*dist_x+dist_y*dist_y);
			if (dist_x < objectsList[i]->getRect()->w/2+objectsList[j]->getRect()->w/2&&
				dist_y < objectsList[i]->getRect()->h/2+objectsList[j]->getRect()->h/2 )
			{
				objectsList[i]->setHealth(objectsList[i]->getHealth() - objectsList[j]->getDamage()/10);
				objectsList[j]->setHealth(objectsList[j]->getHealth() - objectsList[i]->getDamage()/10);	
				
				if (types[i]==2)
				{
					delete objectsList[i];
					objectsList.erase(objectsList.begin()+i);
					types.erase(types.begin()+i);
					
					//i--;
				}
				else if (types[j]==2)
				{
					delete objectsList[j];
					objectsList.erase(objectsList.begin()+j);
					types.erase(types.begin()+j);
					
					//j--;
				}
			}
		}
		
	}
	
	
	for (size_t i=0;i<objectsList.size();i++)
	{
		//printf("%d\n",objectsList[i]->getHealth());
		if (objectsList[i]->getHealth()<=0)
		{
			/*myShip->setHealth(myShip->getHealth()+objectsList[i]->getDamage()*10);
			if (myShip->getHealth()>15000) //need add calc from life points
			{
				myShip->setHealth(15000);
			}*/
			if (objectsList[i]==getMyShip())//cool bug was here if dont this
			{
				myShip->setHealth(0);
				continue;
			}
			points += objectsList[i]->getDamage()/10;
			
			int tmp = types[i];
			
			delete objectsList[i];
			objectsList.erase(objectsList.begin()+i);
			types.erase(types.begin()+i);
			
			i--;
			
			
			if (tmp==0)
			{
				int size = 20+rand()%80;
		
				tmp_surface = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);
				SDL_SetSurfaceBlendMode(tmp_surface,SDL_BLENDMODE_ADD);

				
				//SDL_BlitScaled(loaded_image, NULL, tmp_surface, NULL);
				SDL_BlitScaled(images[0], NULL, tmp_surface, NULL);
				
				
				tmp_rect = new SDL_Rect();
				tmp_rect->x = tmp_rect->y = 0;
				tmp_rect->w = tmp_surface->w;
				tmp_rect->h = tmp_surface->h;
				
				x = rand()%(width-size);
				y = rand()%(height-size);
				sp = -3+6.*rand()/RAND_MAX;

				a = 360.*rand()/RAND_MAX;

				obj = new Asteroid(tmp_rect,tmp_surface,x,y,a,sp);

				objectsList.push_back(obj);
				types.push_back(0);
			}
			else if (tmp==1)
			{
				int size = 20+rand()%40;
				
				//double k = (double)loaded_image->w/loaded_image->h;
				double k = (double)images[1]->w/images[1]->h;
				
				tmp_surface = SDL_CreateRGBSurface(0, k*size, size, 32, 0, 0, 0, 0);
				SDL_SetSurfaceBlendMode(tmp_surface,SDL_BLENDMODE_ADD);

				
				//SDL_BlitScaled(loaded_image, NULL, tmp_surface, NULL);
				SDL_BlitScaled(images[1], NULL, tmp_surface, NULL);
				
				
				tmp_rect = new SDL_Rect();
				tmp_rect->x = tmp_rect->y = 0;
				tmp_rect->w = tmp_surface->w;
				tmp_rect->h = tmp_surface->h;
				
				x = rand()%(width-size);
				y = rand()%(height-size);
				a = 360.*rand()/RAND_MAX;
				
				sp = -1 + rand()%6;
				
				obj = new Spaceship(tmp_rect,tmp_surface,x,y,a,sp,NULL);
				
				objectsList.push_back(obj);
				types.push_back(1);
				
			}
		}
	}
	printf("%d\n",objectsList.size());
	return points;
}

int GameWorld::getWidth()
{
	return width;
}
int GameWorld::getHeight()
{
	return height;
}
vector<DynamicGameObject*>* GameWorld::getObjectsList()
{
	return &objectsList;
}
vector<int>* GameWorld::getTypes()
{
	return &types;
}
	
DynamicGameObject* GameWorld::getMyShip()
{
	return myShip;
}
