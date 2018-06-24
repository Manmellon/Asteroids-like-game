#include "GameObject.h"
class GameInterface : public GameObject
{
	public:
		bool isFocus(int mouseX,int mouseY);
		bool isActive();
};
