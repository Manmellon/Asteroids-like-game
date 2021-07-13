#include "Camera.h"
#include <cmath>
#include <stdio.h>
Camera::Camera(SDL_Rect* r, SDL_Surface *s, double x, double y):DynamicGameObject(r,s,x,y,0,0)
{
	main_surface = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0);
	renderer = SDL_CreateSoftwareRenderer(main_surface);
}

SDL_Surface* Camera::render(GameWorld *world)
{
	vector<DynamicGameObject*> *objects = world->getObjectsList();
	SDL_Rect temp_rect;
	SDL_Texture *tmp_texture;
	SDL_Point center;
	//puts(SDL_GetError());
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
	//SDL_RenderClear(renderer);//why doesnt work ;c
	
	SDL_FillRect(main_surface,NULL,0);
	
	SDL_Rect worldBackRect;
	worldBackRect.x = worldX;
	worldBackRect.y = worldY;
	worldBackRect.w = getRect()->w;
	worldBackRect.h = getRect()->h;
	
	SDL_BlitSurface(world->getSurface(),&worldBackRect,main_surface,NULL);
	
	for (size_t i=0; i<objects->size();i++)
	{
		if ((*objects)[i]->getWorldX()+(*objects)[i]->getRect()->w < worldX||
			(*objects)[i]->getWorldX() > worldX+rect->w||
			(*objects)[i]->getWorldY()+(*objects)[i]->getRect()->h < worldY||
			(*objects)[i]->getWorldY() > worldY+rect->h)
				continue;
		

		temp_rect.x = round((*objects)[i]->getWorldX()-worldX);
		temp_rect.y = round((*objects)[i]->getWorldY()-worldY);
		temp_rect.w = (*objects)[i]->getRect()->w;
		temp_rect.h = (*objects)[i]->getRect()->h;
		
		tmp_texture = SDL_CreateTextureFromSurface(renderer, (*objects)[i]->getSurface());
		//puts(SDL_GetError());
		//printf("%p\n",tmp_texture);
		center.x = (*objects)[i]->getRect()->w/2;
		center.y = (*objects)[i]->getRect()->h/2;
		
		
		SDL_RenderCopyEx(renderer, tmp_texture, NULL, &temp_rect, (*objects)[i]->getAngle(), &center,SDL_FLIP_NONE);
		
		//Debug
		/*SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0);
		SDL_RenderDrawRect(renderer,&temp_rect);
		*/
		
		SDL_DestroyTexture(tmp_texture);
		//SDL_BlitSurface((*objects)[i]->getSurface(),NULL,main_surface,&temp_rect);
	}
	

	return main_surface;
}
