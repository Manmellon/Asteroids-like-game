#include "Button.h"

Button::Button(SDL_Rect *r, /*SDL_Texture *t*/SDL_Surface *s):GameInterface(r,/*t*/s)
{
	
}

bool Button::isActive(Uint32 mouseState, SDL_Event event)
{
	return mouseState == SDL_BUTTON_LEFT&&event.type==SDL_MOUSEBUTTONUP;
}
