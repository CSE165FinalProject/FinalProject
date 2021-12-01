
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
int gameover;
static int timer1, timer2, timer3, timer4;
int timerStarted1, timerStarted2, timerStarted3, timerStarted4;
//Starts up SDL and creates window
bool init();


//Frees media and shuts down SDL
void close();

//Textures
LTexture gDotTexture;
LTexture gBGTexture;
LTexture gBadCloudTexture;
LTexture gGoodCloudTexture;
LTexture gAcidCloudTexture;
void character::render()
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY);
}
void BadCloud::render(int attack)
{
	//show the cloud
	if (attack == 0)
	{
		//show good cloud
		gGoodCloudTexture.render(mPosX, mPosY);
		//gGoodCloudTexture.render(mPosX + 300, mPosY);
	}
	else if(attack == 1)
	{
		//show bad cloud

		gBadCloudTexture.render(mPosX, mPosY);
		//gBadCloudTexture.render(mPosX + 300, mPosY);
	}
	else
	{
		gAcidCloudTexture.render(mPosX, mPosY);
	}
	//gbadcloudtexture.render(mposx, mposy);
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
	gGoodCloudTexture.free();
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
	if (!gGoodCloudTexture.loadFromFile("images/goodcloud.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gAcidCloudTexture.loadFromFile("images/acidrain.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

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
			//printf("%d", timer);
			time_t start, end;
			time_t start1= 0, end1=0;
			time_t start2 = 0, end2=0;
			time_t start3 = 0, end3=0;
			time_t start4= 0, end4=0;
			start = clock();
			//Event handler
			SDL_Event e;

			//Declare the class objects
			character dot;
			BadCloud BCImage[4];
			BadCloud * GCImage = BCImage;
			BadCloud* AcidCloud = BCImage;
			
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
				//GCImage->moveBC();
				//switching to good to bad vice versa
				/*if (timer % 10 > 5)
				{
					GCImage->attackIND = 1;
				}
				else
				{
					BCImage.attackIND = 0;
				}*/
				
				//for (int i = 0; i < 4; i++)
				//{
				//	//randomCLOUDSPAWNDAMAGE = rand() % 10 + 1;
				//	printf("%d", randomCLOUDSPAWNDAMAGE);
				//	if (randomCLOUDSPAWNDAMAGE < 5)
				//	{
				//		BCImage[i].attack(BCImage[i], dot);
				//	}
				//}
				int randomCLOUDSPAWNDAMAGE = 0;
				srand(time(NULL));
				randomCLOUDSPAWNDAMAGE = rand() % 100 + 1;
				int choosing;
				choosing = randomCLOUDSPAWNDAMAGE;
				if (timer %20 <= 5&& timerStarted1 == 0)
				{
					start1 = clock();
					timerStarted1 = 1;
					//BCImage[0].attack(BCImage[0], dot);
				}
				else if (timer % 20 > 5 && timer % 20 <= 10 && timerStarted2 == 0)
				{
					start2 = clock();
					timerStarted2 = 1;
					//BCImage[1].attack(BCImage[1], dot);
				}
				else if (timer % 20 > 10 && timer % 20 <= 15 && timerStarted3 == 0)
				{
					start3 = clock();
					timerStarted3 = 1;
					//BCImage[2].attack(BCImage[2], dot);
				}
				else if (timer % 20 > 15 && timer % 20 <= 20 && timerStarted4 == 0)
				{
					start4 = clock();
					timerStarted4 = 1;
					//BCImage[3].attack(BCImage[3], dot);
				}
				//printf("%d\n", timerStarted1);
				//BCImage[0].attack(BCImage[0], dot);
				//BCImage[1].attack(BCImage[1], dot);
				//BCImage[2].attack(BCImage[2], dot);
				//BCImage[3].attack(BCImage[3], dot);
				BCImage[0].moveBC();
				BCImage[1].moveBC();
				BCImage[2].moveBC();
				BCImage[3].moveBC();
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
				gBGTexture.render(0,0);
				//gBGTexture.render(0, scrollingOffset);
				//gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);
				//gBGTexture.render(0, scrollingOffset + gBGTexture.getHeight());
				//Render objects
				detectingCLOUD(BCImage[0], dot);
				detectingCLOUD(BCImage[1], dot);
				detectingCLOUD(BCImage[2], dot);
				detectingCLOUD(BCImage[3], dot);
				dot.render();
			
				/*if (choosing > 0 && choosing <= 25)
				{
					BCImage[0].render(BCImage[0].attackIND);
					BCImage[1].render(BCImage[1].attackIND);
					BCImage[2].render(BCImage[2].attackIND);
				}*/
				BCImage[0].render(BCImage[0].attackIND);
				BCImage[1].render(BCImage[1].attackIND);
				BCImage[2].render(BCImage[2].attackIND);
				BCImage[3].render(BCImage[3].attackIND);
				//Update screen
				SDL_RenderPresent(gRenderer);
				end = clock();
				if (timerStarted1 == 1)
				{
					end1 = clock();
					BCImage[0].attack(BCImage[0], dot);
				}
				if (timerStarted2 == 1)
				{
					end2 = clock();
					BCImage[1].attack(BCImage[1], dot);
					
				}
				if (timerStarted3 == 1)
				{
					end3 = clock();
					BCImage[2].attack(BCImage[2], dot);
				}
				if (timerStarted4 == 1)
				{
					end4 = clock();
					BCImage[3].attack(BCImage[3], dot);
				}
				
				/*end1 = clock();
				end2 = clock();
				end3 = clock();
				end4 = clock();*/
				//( (double)(newTime-oldTime)/CLOCKS_PER_SEC ) ;
				timer = ((double)(end - start) / CLOCKS_PER_SEC);
				timer1 = ((double)(end1 - start1) / CLOCKS_PER_SEC);
				timer2 = ((double)(end2 - start2) / CLOCKS_PER_SEC);
				timer3 = ((double)(end3 - start3) / CLOCKS_PER_SEC);
				timer4 = ((double)(end4 - start4) / CLOCKS_PER_SEC);
				if (gameover == 1)
				{
					quit = true;
				}
				//printf("%d\n", gameover);
				//Attack indicator

			}
			
		}
		
	}

	//Free resources and close SDL
	close();

	return 0;
}