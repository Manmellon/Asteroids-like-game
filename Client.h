#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>

#include "GameInterface.h"

using namespace std;
class Client
{
	protected:
		enum {MENU,GAME,PAUSE,OPTIONS,HELP,EXIT}gameState;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event event;
		SDL_DisplayMode displayMode;
		SDL_Cursor *defaultCursor,*activeCursor;
		int mouseX, mouseY;
		Uint32 mouseState;
	
		vector< vector<GameInterface*> > interfacesList;
		void CheckInterface();
	public:
		Client();
		int MainLoop();
		~Client();
};
