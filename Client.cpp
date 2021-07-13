#include "Client.h"
#include "Button.h"
#include "Laser.h"
#include "Spaceship.h"

#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_TTF.h>

#include <iostream>
#include <cstring>
Client::Client()
{
	SDL_Surface *loaded_image;
		
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GetCurrentDisplayMode(0, &displayMode);

	
	window = SDL_CreateWindow(
		"The Day of Saggitarius III",
		/*displayMode.w/4,
		displayMode.h/4,
		displayMode.w/2,
		displayMode.h/2,*/
		0,0,
		displayMode.w,
		displayMode.h,
		0
		);
	SDL_GetWindowSize(window, &window_w, &window_h);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	TTF_Init();
	
	
	defaultCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	activeCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	
	font = TTF_OpenFont("Algeria2.ttf",70);
	

	
	loaded_image = IMG_Load("menu_background.jpg");
	background = SDL_CreateTextureFromSurface(renderer, loaded_image);
	SDL_FreeSurface(loaded_image);
	
	loaded_image = IMG_Load("button.png");
	//SDL_Texture *tmp_texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
	SDL_Rect *tmp_rect=new SDL_Rect;
	
	camera_place = new SDL_Rect;
	camera_place->x = 0;
	camera_place->y = 0;
	camera_place->w = window_w * 0.75;
	camera_place->h = window_h;
	
	camera_rect = new SDL_Rect;
	camera_rect->x = 0;
	camera_rect->y = 0;
	
	camera_rect->w = 400;//400
	camera_rect->h = 400;
	
	for (int i=0;i<EXIT+1;i++)
	{
		interfacesList.push_back(vector<GameInterface*>());
	}
	
	tmp_rect->w = window_w/4;
	tmp_rect->h = window_h/8;
	tmp_rect->x = window_w/2-tmp_rect->w/2;
	//tmp_rect->y = window_h*7/8-tmp_rect->h/2;
	
	SDL_Surface *text_surface,*tmp_surface;

	SDL_Color text_color;

	
	text_color.r = 0;
	text_color.g = 0;
	text_color.b = 0;
	
	
	text_surface =  TTF_RenderUTF8_Solid(font,"  Exit", text_color);

	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, tmp_rect->x, window_h*0.9-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,MAIN_MENU);
	SDL_FreeSurface(text_surface);
	
	//*****
	//font = TTF_OpenFont("Algeria2.ttf",70);
	text_surface =  TTF_RenderUTF8_Solid(font,"  Play", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, tmp_rect->x, window_h*0.7-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,MAIN_MENU);
	SDL_FreeSurface(text_surface);
	//*****
	text_surface =  TTF_RenderUTF8_Solid(font,"  Back", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, tmp_rect->x, window_h*0.9-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,PLAY_MENU);
	SDL_FreeSurface(text_surface);
	//******
	font = TTF_OpenFont("Algeria2.ttf",48);
	text_surface =  TTF_RenderUTF8_Solid(font,"Load Game", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, tmp_rect->x, window_h*0.6-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,PLAY_MENU);
	SDL_FreeSurface(text_surface);
	//******
	text_surface =  TTF_RenderUTF8_Solid(font,"New Game", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, tmp_rect->x, window_h*0.450-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,PLAY_MENU);
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	//******
	font = TTF_OpenFont("Algeria2.ttf",70);
	text_surface =  TTF_RenderUTF8_Solid(font," Pause", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, camera_place->x+camera_place->w, window_h*0.1-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,GAME);
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	//******
	font = TTF_OpenFont("Algeria2.ttf",48);
	text_surface =  TTF_RenderUTF8_Solid(font,"Continue", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, camera_place->x+camera_place->w*0.75, window_h*0.2-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,PAUSE);
	SDL_FreeSurface(text_surface);
	//TTF_CloseFont(font);
	//******
	//font = TTF_OpenFont("Algeria2.ttf",48);
	text_surface =  TTF_RenderUTF8_Solid(font,"Save Game", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, camera_place->x+camera_place->w*0.75, window_h*0.4-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,PAUSE);
	SDL_FreeSurface(text_surface);
	//******
	text_surface =  TTF_RenderUTF8_Solid(font,"  Menu", text_color);
	
	tmp_surface = SDL_CreateRGBSurface(0, tmp_rect->w,tmp_rect->h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(loaded_image,NULL,tmp_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,tmp_surface,NULL);
	
	addInterface(tmp_surface, camera_place->x+camera_place->w*0.75, window_h*0.8-tmp_rect->h/2, tmp_rect->w,tmp_rect->h,0,PAUSE);
	SDL_FreeSurface(text_surface);
	
	//******
	
	
	gameState = MAIN_MENU;
	oldGameState = MAIN_MENU;
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
		//puts("While starts");
		ms=SDL_GetTicks();
		
		mouseState = SDL_GetMouseState(&mouseX,&mouseY);
		keys = SDL_GetKeyboardState(NULL);
		
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT: quit=1; break;
		}
		
		CheckInterface();
		//puts("CheckInterface ends");
		if (gameState == EXIT)
		{
			quit = 1;
		}
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
		SDL_RenderClear(renderer);
		
		Draw();
		//puts("Draw ends");
		DrawInterface();
		//puts("DrawInterface ends");
		SDL_RenderPresent(renderer);
		
		ms = SDL_GetTicks()-ms;
		//cout<<ms<<endl;
		if (ms < MSPF)
			SDL_Delay(MSPF-ms);
	}
	return 0;
}
void Client::addInterface(SDL_Surface *s,int x, int y, int w, int h, int type, int gs)
{
	SDL_Rect *r = new SDL_Rect;
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
	GameInterface *interface;
	switch (type)
	{
		case 0:
		{
			interface = new Button(r,/*t*/s);
		}break;
	}
	interfacesList[gs].push_back(interface);
}

void Client::Draw()
{
	switch (gameState)
	{
		case MAIN_MENU:
		{
			SDL_RenderCopy(renderer, background, NULL, NULL);
		}break;
		case PLAY_MENU:
		{
			SDL_RenderCopy(renderer, background, NULL, NULL);
		}break;
		case GAME:
		{
			gameparty->setPoints(gameparty->getPoints()+gameparty->getWorld()->update());
			//gameparty->getWorld()->update();
			gameparty->getCamera()->setWorldX(
				gameparty->getWorld()->getMyShip()->getWorldX() - 
				gameparty->getCamera()->getRect()->w/2);
			gameparty->getCamera()->setWorldY(
				gameparty->getWorld()->getMyShip()->getWorldY() - 
				gameparty->getCamera()->getRect()->h/2);
			
			//std::cout<<(gameparty->getWorld()->getMyShip()->getHealth())<<std::endl;
			SDL_SetRenderDrawColor(renderer, 0x88, 0x88, 0x88, 0);
			SDL_RenderFillRect(renderer,NULL);
			
			camera_surface = gameparty->getCamera()->render(gameparty->getWorld());
			camera_texture = SDL_CreateTextureFromSurface(renderer,camera_surface);
			SDL_RenderCopy(renderer,camera_texture,NULL,camera_place);
			
			SDL_DestroyTexture(camera_texture);
			
			
			int life = gameparty->getWorld()->getMyShip()->getHealth();
			char strLife[20]={0};
			sprintf(strLife, "%d/15000", life);//need add calc from life points
			//printf("%d\n",life);
			font = TTF_OpenFont("Algeria2.ttf",44);

			SDL_Rect rect;
			SDL_Color text_color;
			text_color.r = 0;
			text_color.g = 0;
			text_color.b = 0;
			
			SDL_Surface *text_surface =  TTF_RenderUTF8_Solid(font,strLife, text_color);
			SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
			
			SDL_GetClipRect(text_surface, &rect);
			SDL_FreeSurface(text_surface);
			rect.x = camera_place->w;
			rect.y = window_h/2;
			SDL_RenderCopy(renderer, text_texture, NULL, &rect);

			SDL_DestroyTexture(text_texture);
			
			
			text_surface = TTF_RenderUTF8_Solid(font,"Health", text_color);
			text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
			
			SDL_GetClipRect(text_surface, &rect);
			SDL_FreeSurface(text_surface);
			rect.x = camera_place->w;
			rect.y = window_h/2-50;
			SDL_RenderCopy(renderer, text_texture, NULL, &rect);

			SDL_DestroyTexture(text_texture);
			
			
			text_surface = TTF_RenderUTF8_Solid(font,"Points", text_color);
			text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
			
			SDL_GetClipRect(text_surface, &rect);
			SDL_FreeSurface(text_surface);
			rect.x = camera_place->w;
			rect.y = window_h/2-150;
			SDL_RenderCopy(renderer, text_texture, NULL, &rect);

			SDL_DestroyTexture(text_texture);


			sprintf(strLife, "%d", gameparty->getPoints());
			text_surface =  TTF_RenderUTF8_Solid(font,strLife, text_color);
			text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
			
			SDL_GetClipRect(text_surface, &rect);
			SDL_FreeSurface(text_surface);
			rect.x = camera_place->w;
			rect.y = window_h/2-100;
			SDL_RenderCopy(renderer, text_texture, NULL, &rect);

			SDL_DestroyTexture(text_texture);
			
			
			TTF_CloseFont(font);
			
	
		}break;
		case PAUSE:
		{
			//std::cout<<"in Draw";
			SDL_Surface *pause_surface = SDL_CreateRGBSurface(0, window_w, window_h, 32, 0, 0, 0, 0);
			SDL_SetSurfaceBlendMode(pause_surface,SDL_BLENDMODE_BLEND);
			SDL_FillRect(pause_surface, NULL, 0x88888888);
			SDL_BlitSurface(camera_surface,NULL,pause_surface,NULL);
			
			SDL_Texture *pause_texture = SDL_CreateTextureFromSurface(renderer, pause_surface);
			SDL_RenderCopy(renderer,pause_texture,NULL,NULL);
			SDL_FreeSurface(pause_surface);
			SDL_DestroyTexture(pause_texture);
			
		}break;
		case EXIT:
		{
		}break;
	}
}

void Client::DrawInterface()
{
	unsigned int i;
	SDL_Rect *rect;
	SDL_Surface *surface;
	SDL_Texture *texture;
	
	for (i=0;i<interfacesList[gameState].size();i++)
	{
		//texture = interfacesList[gameState][i]->getTexture();
		surface = interfacesList[gameState][i]->getSurface();
		texture = SDL_CreateTextureFromSurface(renderer,surface);
		rect = interfacesList[gameState][i]->getRect();
		
		SDL_RenderCopy(renderer, texture, NULL, rect);

		SDL_DestroyTexture(texture);
	}
}

void Client::CheckInterface()
{
	unsigned int i;
	bool needChangeCursor = false;
	
	//keys checking
	switch (gameState)
	{
		case MAIN_MENU:
		{
		}break;
		case PLAY_MENU:
		{
		}break;
		case GAME:
		{
			if (gameparty->getWorld()->getMyShip()->getHealth()<=0)
			{
				gameparty->getWorld()->getMyShip()->setHealth(0);
				saveResult(gameparty->getPoints());
				delete gameparty;
				oldGameState = gameState;
				gameState = MAIN_MENU;
				break;
			}
			
			gameparty->getWorld()->getMyShip()->setSpeed(0);
			if (keys[SDL_SCANCODE_W])
			{
				
				if (keys[SDL_SCANCODE_LSHIFT])
				{
					gameparty->getWorld()->getMyShip()->setSpeed(4);
				}
				else
				{
					gameparty->getWorld()->getMyShip()->setSpeed(1);
				}
			}
			if (keys[SDL_SCANCODE_A])
			{
				if (keys[SDL_SCANCODE_LSHIFT])
				{
					gameparty->getWorld()->getMyShip()->rotate(-5);
				}
				else
				{
					gameparty->getWorld()->getMyShip()->rotate(-1);
				}
			}
			if (keys[SDL_SCANCODE_D])
			{
				if (keys[SDL_SCANCODE_LSHIFT])
				{
					gameparty->getWorld()->getMyShip()->rotate(5);
				}
				else
				{
					gameparty->getWorld()->getMyShip()->rotate(1);
				}
			}
			if (keys[SDL_SCANCODE_S])
			{
				gameparty->getWorld()->getMyShip()->setSpeed(-1);
			}
			if (keys[SDL_SCANCODE_SPACE])
			{
				
				Laser *tmp_laser = ((Spaceship*)(gameparty->getWorld()->getMyShip()))->shootLaser();
				gameparty->getWorld()->getObjectsList()->push_back(tmp_laser);
				gameparty->getWorld()->getTypes()->push_back(2);
			}
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				oldGameState = gameState;
				gameState = PAUSE;
			}
			
			
		}break;
		case PAUSE:
		{
		}break;
		case EXIT:
		{			
		}break;
	}
	
	for (i=0;i<interfacesList[gameState].size();i++)
	{
		if (interfacesList[gameState][i]->isFocus(mouseX,mouseY))
		{
			SDL_SetCursor(activeCursor);
			if (interfacesList[gameState][i]->isActive(mouseState, event))
			{	
				switch (gameState)
				{
					case MAIN_MENU:
					{
						CheckMainMenuInterface(i);
					}break;
					case PLAY_MENU:
					{
						CheckPlayMenuInterface(i);
					}break;
					case GAME:
					{
						CheckGameInterface(i);
					}break;
					case PAUSE:
					{
						CheckPauseInterface(i);
					}break;
				
					case EXIT:
					{
						
					}break;
				}
			}
			needChangeCursor = true;
		}
		//else SDL_SetCursor(defaultCursor);
	}
	if (!needChangeCursor)
	{
		SDL_SetCursor(defaultCursor);
	}
}

void Client::CheckMainMenuInterface(int i)
{
	switch (i)
	{
		case 0:
		{
			oldGameState = gameState;
			gameState = EXIT;
		}break;
		case 1:
		{
			oldGameState = gameState;
			gameState = PLAY_MENU;
		}break;
	}
}

void Client::CheckPlayMenuInterface(int i)
{
	switch (i)
	{
		case 0:
		{
			oldGameState = gameState;
			gameState = MAIN_MENU;

		}break;
		case 1:
		{
			gameparty = new GameParty(renderer, camera_rect);
			gameparty->loadGame();
			oldGameState = gameState;
			gameState = GAME;
		}break;
		case 2:
		{
			//new game
			gameparty = new GameParty(renderer, camera_rect);
			oldGameState = gameState;
			gameState = GAME;
		}break;
	}
}

void Client::CheckGameInterface(int i)
{
	switch (i)
	{
		case 0:
		{
			oldGameState = gameState;
			gameState = PAUSE;
		}break;
	}
}

void Client::CheckPauseInterface(int i)
{
	switch (i)
	{
		case 0:
		{
			oldGameState = gameState;
			gameState = GAME;
		}break;
		case 1:
		{
			gameparty->saveGame();
		}break;
		
		case 2:
		{
			oldGameState = gameState;
			gameState = MAIN_MENU;
			delete gameparty;
		}break;
	}
}

void Client::saveResult(int n)
{
	FILE *f = fopen("results.dat","rb");
	int size;
	fread(&size, sizeof(int),1,f);
	int *arr = (int*) malloc(size*sizeof(int)+1);
	for (int i=0;i<size;i++)
	{
		fread(&arr[i], sizeof(int), 1, f);
	}
	arr[size] = n;
	//sort here
	fclose(f);
}
