#include "Client.h"

Client::Client()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GetCurrentDisplayMode(0, &displayMode);
	
	window = SDL_CreateWindow(
		"The Day of Saggitarius III",
		displayMode.w/4,
		displayMode.h/4,
		displayMode.w/2,
		displayMode.h/2,
		0
		);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	defaultCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	activeCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	
	
	gameState = MENU;
}

Client::~Client()
{
}

int Client::MainLoop()
{
	int quit=0;
	Uint32 ms;
	int FPS = 60;
	Uint32 MSPF = 1000/FPS;
	
	while (!quit)
	{
		ms=SDL_GetTicks();
		
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT: quit=1; break;
		}
		
		CheckInterface();
		
		SDL_RenderPresent(renderer);
		
		ms = SDL_GetTicks()-ms;

		if (ms < MSPF)
			SDL_Delay(MSPF-ms);
	}
	return 0;
}

void Client::CheckInterface()
{
	SDL_SetCursor(defaultCursor);
	mouseState = SDL_GetMouseState(&mouseX,&mouseY);
	for (int i=0;i<interfacesList[gameState].size();i++)
	{
		if (interfacesList[gameState][i]->isFocus(mouseX,mouseY))
		{
			SDL_SetCursor(activeCursor);
		}
		
	}
}
