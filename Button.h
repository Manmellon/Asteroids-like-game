#ifndef BUTTON_H_
#define BUTTON_H_
#include "GameInterface.h"
class Button : public GameInterface
{
	public:
		Button(SDL_Rect *r, /*SDL_Texture *t*/SDL_Surface *s);
		bool isActive(Uint32 mouseState, SDL_Event event);
};
#endif
