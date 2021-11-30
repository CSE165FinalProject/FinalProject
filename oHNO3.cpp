
//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include "objects/character.h"
#include "objects/cloud.h"
//#include "objects/character.h"
#include "objects/LTexture.h"
#include "detectingCLOUD.h"
//#include "createSDLWIN.h"
//#include "imageloader.cpp"
//Screen dimension constants
extern const int SCREEN_WIDTH = 944;
extern const int SCREEN_HEIGHT = 500;
bool quit;
int timer;

//Starts up SDL and creates window
bool init();


//Frees media and shuts down SDL
void close();

//Textures
LTexture gDotTexture;
LTexture gBGTexture;
LTexture gBadCloudTexture;
void character::render()
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY);
}
void BadCloud::render()
{
	//Show the Cloud
	gBadCloudTexture.render(mPosX, mPosY);
}
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
void close()
{
	//Free loaded images
	gDotTexture.free();
	gBGTexture.free();
	gBadCloudTexture.free();
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gDotTexture.loadFromFile("images/dot.bmp"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load background texture
	if (!gBGTexture.loadFromFile("images/clouds.jpg"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	//Loud Bad Cloud
	if (!gBadCloudTexture.loadFromFile("images/badcloud.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	//Load Attack

	return success;
}

int main(int argc, char* args[])
{
	//timer = 0;
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			quit = false;
			//timer++;
			//Event handler
			SDL_Event e;

			//Declare the class objects
			character dot;
			BadCloud BCImage;
			//The background moving
			int scrollingOffset = 0;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent(e);
					//BCImage.movementBADCLOUD();
				}
				
				//Move the dot
				dot.move();
				BCImage.moveBC();
				//Scroll background
				--scrollingOffset;
				if (scrollingOffset < -gBGTexture.getHeight())
				{
					scrollingOffset = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				
				//Render background
				//gBGTexture.render(scrollingOffset, 0);
				gBGTexture.render(0, scrollingOffset);
				//gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);
				gBGTexture.render(0, scrollingOffset + gBGTexture.getHeight());
				//Render objects
				detectingCLOUD(BCImage, dot);
				dot.render();
				BCImage.render();
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}