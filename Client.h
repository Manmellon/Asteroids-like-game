class Client
{
	protected:
		enum {MENU,GAME,PAUSE,OPTIONS,HELP,EXIT}gameState;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event event;
		SDL_DisplayMode displayMode;
	public:
		Client();
		int MainLoop();
		~Client();
}
