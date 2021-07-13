#ifndef GAMEPARTY_H_
#define GAMEPARTY_H_
#include "GameWorld.h"
#include "Camera.h"
#include "Player.h"
class GameParty
{
	protected:
		GameWorld *world;
		Camera *camera;
		int points;
	public:
		GameParty(SDL_Renderer *renderer, SDL_Rect *camera_rect);
		~GameParty();
		void loadGame();
		void saveGame();
		GameWorld* getWorld();
		Camera* getCamera();
		int getPoints();
		void setPoints(int);
};
#endif
