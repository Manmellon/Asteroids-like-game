#ifndef CAMERA_H_
#define CAMERA_H_
#include "DynamicGameObject.h"
#include "GameWorld.h"
class Camera : public DynamicGameObject
{
	protected:
		
		SDL_Renderer *renderer;
		SDL_Surface *main_surface;
	public:
		Camera(SDL_Rect* r, SDL_Surface *s, double x, double y);
		//SDL_Texture* render(GameWorld*);
		SDL_Surface* render(GameWorld*);
};
#endif
