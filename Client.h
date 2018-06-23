#include <SDL2/SDL.h>

class Client
{
	protected:
		enum {MENU,GAME,PAUSE,OPTIONS,HELP,EXIT}gameState;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event event;
		SDL_DisplayMode displayMode;
		void CheckInterface();
	public:
		Client();
		int MainLoop();
		~Client();
};
