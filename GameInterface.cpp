#include "GameInterface.h"
GameInterface::GameInterface(SDL_Rect *r, /*SDL_Texture *t*/SDL_Surface *s):GameObject(r,/*t*/s)
{

}
bool GameInterface::isFocus(int mouseX,int mouseY)
{
	if (rect)
	return mouseX>=rect->x&&mouseX<=rect->x+rect->w
		   &&mouseY>=rect->y&&mouseY<=rect->y+rect->h;
	else return false;
}
