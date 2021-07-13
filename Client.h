#ifndef CLIENT_H_
#define CLIENT_H_
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_ttf.h>

#include "GameInterface.h"
#include "GameParty.h"

using namespace std;
class Client
{
	protected:
		enum {MAIN_MENU,PLAY_MENU,GAME,PAUSE,EXIT}gameState,oldGameState;
		SDL_Window *window;
		int window_w,window_h;
		SDL_Renderer *renderer;
		SDL_Event event;
		SDL_DisplayMode displayMode;
		SDL_Cursor *defaultCursor,*activeCursor;
		int mouseX, mouseY;
		Uint32 mouseState;
		const Uint8 *keys;
		TTF_Font *font;
		SDL_Texture *background;
		
		vector< vector<GameInterface*> > interfacesList;
		GameParty *gameparty;
		SDL_Surface *camera_surface;
		SDL_Texture *camera_texture;
		SDL_Rect *camera_place;
		SDL_Rect *camera_rect;
		
		void addInterface(/*SDL_Texture* t*/SDL_Surface *s, int x, int y, int w, int h, int type, int gs);
		void Draw();
		void DrawInterface();
		void CheckInterface();
		void CheckMainMenuInterface(int i);
		void CheckPlayMenuInterface(int i);
		void CheckGameInterface(int i);
		void CheckPauseInterface(int i);
		void saveResult(int n);
		public:
		Client();
		int MainLoop();
		~Client();
};
#endif
