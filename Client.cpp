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
	
	gameState = MENU;
}

Client::~Client()
{
}

int Client::MainLoop()
{
	int quit=0;
	
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT: quit=1; break;
		}
		SDL_RenderPresent(renderer);
	}
	return 0;
}
