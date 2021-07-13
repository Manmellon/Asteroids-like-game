#ifndef GAMEINTERFACE_H_
#define GAMEINTERFACE_H_
#include "GameObject.h"
class GameInterface : public GameObject
{
	public:
		GameInterface(SDL_Rect *r, SDL_Surface *s);

		bool isFocus(int mouseX,int mouseY);
		virtual bool isActive(Uint32 mouseState, SDL_Event event)=0;
};
#endif
