//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc Vedaant Vyas
//Nov 17, 2021
//

#ifdef __linux__ 
#include <GL/glut.h>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include "objects/character.h"
#include "objects/cloud.h"
#include "objects/LTexture.h"
#include "detection.h"
#include <SOIL/SOIL.h>
#include <SOIL/image_DXT.h>
#include <GL/glut.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include "global.h"

#elif _WIN32

#include <gl/glut.h>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include "objects/character.h"
#include "objects/cloud.h"
#include "objects/LTexture.h"
#include "detection.h"
#include <SOIL/SOIL.h>
#include <SOIL/image_dxt.h>
#include <GL/glut.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include "global.h"
#else

#endif

//Screen dimension constants
using namespace std;
extern const int SCREEN_WIDTH = 944;
extern const int SCREEN_HEIGHT = 500;
bool quit;
bool tryAgain;
bool quitSOILEX;
int timer;
int gameover;
int life;
int powerupLifetime;
int survivehighscore;
int fullHEALTH;
int timer1, timer2, timer3, timer4, cooldowntimer;
int timerStarted1, timerStarted2, timerStarted3, timerStarted4;
//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Textures
GLuint death;
LTexture gPlayerTexture;
LTexture gBGTexture;
LTexture gBadCloudTexture;
LTexture gGoodCloudTexture;
LTexture gAcidCloudTexture;
LTexture gBGTextureLater;
LTexture gTextTexture;
LTexture gHighScoreText;
LTexture gPowerUp;
LTexture gLife;
LTexture gFHealth;
//Font
TTF_Font* gFont = NULL;

//render
void powerup::render()
{
	//show powerup
	gPowerUp.render(mPosX, mPosY);
}
void character::render()
{
	//Show the player
	gPlayerTexture.render(mPosX, mPosY);
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
void loadTextures() {
	death = SOIL_load_OGL_texture
	(
		"images/go.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}
void loadTEXTTEXTURES()
{
	//load text
	//printf("%d\n", timer);
	//gTextTexture.render(((SCREEN_WIDTH - gTextTexture.getWidth()) / 2), (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
	gTextTexture.render(0, 0);
	gHighScoreText.render(SCREEN_WIDTH - gHighScoreText.getWidth(), 0);
	gLife.render(300, 0);
	gFHealth.render(0, 600);
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
		gWindow = SDL_CreateWindow("oHN03", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

				//Initialize ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
//Display death screen using glut and soil
void disDeath()
{
	//display death screen
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, death);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(640, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(640, 480);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 480);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Display Surviving Time
	string ST = "Surviving Time: ";
	ST += to_string(timer);
	int len = ST.size();
	glRasterPos2f(300, 260);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ST[i]);
	}

	//Display Highest Surviving Time
	string SHT = "Surviving Highest Time: ";
	SHT += to_string(survivehighscore);
	int len1 = SHT.size();
	glRasterPos2f( 300, 240);
	for (int i = 0; i < len1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, SHT[i]);
	}
	if (timer > survivehighscore)
	{
		//display acknowledgement of new high score
		string congratuation = "NEW HIGHSCORE!!";
		int len2 = congratuation.size();
		glRasterPos2f(300, 220);
		for (int i = 0; i < len2; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, congratuation[i]);
		}
	}
	//display text
	/*string NG = "Press N to try again game or M to quit";
	int len = NG.size();
	glRasterPos2f(280 - len / 2, 220);

	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, NG[i]);
	}*/
	glFlush();

}
void close()
{
	//Free loaded images
	gPlayerTexture.free();
	gBGTexture.free();
	gBadCloudTexture.free();
	gGoodCloudTexture.free();
	gTextTexture.free();
	gPowerUp.free();
	
	//Font
	TTF_CloseFont(gFont);
	gFont = NULL;
	
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
//if you want to initialize something in soil
void initializeSOIL()
{
	//initialize soil variables
}
//Soil init function
void myInitSOIL()
{
	//startup SOIL
	glClearColor(1.0, 4.0, 6.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	loadTextures();
	initializeSOIL();
}
//Glut Idle
void idleFunc()
{
	//idle 
	glutPostRedisplay();
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//Load powerup texture
	if (!gPowerUp.loadFromFile("images/powerup.png"))
	{
		printf("Failed to load powerup texture!\n");
		success = false;
	}
	//Load player texture
	if (!gPlayerTexture.loadFromFile("images/player.png"))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}
	 
	//Load background texture
	if (!gBGTexture.loadFromFile("images/goodland.jpg"))
	{
		printf("Failed to load good background texture!\n");
		success = false;
	}
	//Load background texture
	if (!gBGTextureLater.loadFromFile("images/damageland.jpg"))
	{
		printf("Failed to load bad background texture!\n");
		success = false;
	}
	//Loud Warning Cloud
	if (!gBadCloudTexture.loadFromFile("images/badcloud.png"))
	{
		printf("Failed to load Warning cloud texture!\n");
		success = false;
	}
	//Load good cloud
	if (!gGoodCloudTexture.loadFromFile("images/goodcloud.png"))
	{
		printf("Failed to load goodcloud texture!\n");
		success = false;
	}
	//load acid cloud
	if (!gAcidCloudTexture.loadFromFile("images/acidrain.png"))
	{
		printf("Failed to load acid rain texture!\n");
		success = false;
	}
	
	//load font
	gFont = TTF_OpenFont("images/gameFONT.ttf",20);
	if (gFont == NULL)
	{
		printf("Failed to load font: %s\n", TTF_GetError());
		success = false;

	}
	else
	{
		SDL_Color textcolor = { 0,0,0 };
		string s = to_string(timer);
		if (!gTextTexture.loadFromRenderedText(s, textcolor))
		{
			printf("Failed to render game timer");
			success = false;
		}
	}
	
	return success;
}
//void glutLeaveMainLoop(void);
void keyFunc(unsigned char k, int x, int y)
{
	//end screen keyboard input
	if (k == 'n' || k == 'N')
	{
		//printf("Hello");
		/*initializeSOIL();
		glutPostRedisplay();*/
		tryAgain = false;
		printf("%d", tryAgain);
		quitSOILEX = true;
		//init();
		
	}
	else if (k == 'm' || k == 'M')
	{
		tryAgain = true;
		quitSOILEX = true;
	}
}

int main(int argc, char* argv[])
{
	//timer = 0;
	tryAgain = false;
	powerupLifetime = 0;
	//Start up SDL and create window
	while (!tryAgain)
	{
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
				//getting Highscore
				ifstream fgetdata("data/survivetime.txt");
				fgetdata >> survivehighscore;
				fgetdata.close();
				//Initializing time for diff clouds
				time_t start, end;
				time_t start1 = 0, end1 = 0;
				time_t start2 = 0, end2 = 0;
				time_t start3 = 0, end3 = 0;
				time_t start4 = 0, end4 = 0;
				start = clock();
				
				//Event handler
				SDL_Event e;

				//Declare the class objects
				character player;
				BadCloud BCImage[4];
				//BadCloud* GCImage = BCImage;
				//BadCloud* AcidCloud = BCImage;
				powerup powerups;
				//The background moving
				//int scrollingOffset = 0;

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

						//Handle input for the player
						player.handleEvent(e);
						//BCImage.movementBADCLOUD();
					}

					//Move the Player
					player.move();


					//Start Timer at diff. instances for diff. clouds
					if (timer % 20 <= 5 && timerStarted1 == 0)
					{
						start1 = clock();
						timerStarted1 = 1;

					}
					else if (timer % 20 > 5 && timer % 20 <= 10 && timerStarted2 == 0)
					{
						start2 = clock();
						timerStarted2 = 1;
					}
					else if (timer % 20 > 10 && timer % 20 <= 15 && timerStarted3 == 0)
					{
						start3 = clock();
						timerStarted3 = 1;

					}
					else if (timer % 20 > 15 && timer % 20 <= 20 && timerStarted4 == 0)
					{
						start4 = clock();
						timerStarted4 = 1;

					}

					//Cloud Move
					BCImage[0].moveBC();
					BCImage[1].moveBC();
					BCImage[2].moveBC();
					BCImage[3].moveBC();

					//Scroll background
					/*--scrollingOffset;
					if (scrollingOffset < -gBGTexture.getHeight())
					{
						scrollingOffset = 0;
					}*/

					
					
					

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);
					
					//Change Background overtime
					if (timer > 50)
					{
						gBGTextureLater.render(0, 0);
					}
					else
					{
						gBGTexture.render(0, 0);
					}
					//gPowerUp.render(100, 100);
					//gBGTexture.render(0, scrollingOffset);
					//gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);
					//gBGTexture.render(0, scrollingOffset + gBGTexture.getHeight());

					//Detecting objects
					detectingCLOUD(BCImage[0], player);
					detectingCLOUD(BCImage[1], player);
					detectingCLOUD(BCImage[2], player);
					detectingCLOUD(BCImage[3], player);
					
					//Render objects
					player.render();
					/*BCImage[0].render(BCImage[0].attackIND);
					BCImage[1].render(BCImage[1].attackIND);
					BCImage[2].render(BCImage[2].attackIND);
					BCImage[3].render(BCImage[3].attackIND);*/

					//Pick random coordinates for powerup
					powerups.spawn();
					//Render powerups
					powerups.render();
					
					//if timer started for each cloud, render and start attacking phase
					if (timerStarted1 == 1)
					{
						end1 = clock();
						BCImage[0].attack(BCImage[0], player);
						BCImage[0].render(BCImage[0].attackIND);
					}
					if (timerStarted2 == 1)
					{
						end2 = clock();
						BCImage[1].attack(BCImage[1], player);
						BCImage[1].render(BCImage[1].attackIND);

					}
					if (timerStarted3 == 1)
					{
						end3 = clock();
						BCImage[2].attack(BCImage[2], player);
						BCImage[2].render(BCImage[2].attackIND);
					}
					if (timerStarted4 == 1)
					{
						end4 = clock();
						BCImage[3].attack(BCImage[3], player);
						BCImage[3].render(BCImage[3].attackIND);
					}
					
					

					//Detect powerup if player is near
					detectionPOWERUP(powerups, player);
					
					//show timer
					//load text, health, timer, high timer score
					loadTEXTTEXTURES();

					//update screen
					SDL_RenderPresent(gRenderer);

					//Get time
					end = clock();
					
					//Random speed boost initalizer
					int randomSpeedBoost;
					srand(time(NULL));
					randomSpeedBoost = rand() % 10 + 0;

					//calculate time
					timer = ((double)(end - start) / CLOCKS_PER_SEC);
					timer1 = ((double)(end1 - start1) / CLOCKS_PER_SEC) + (randomSpeedBoost *0.2);
					timer2 = ((double)(end2 - start2) / CLOCKS_PER_SEC) + (randomSpeedBoost * 0.2);
					timer3 = ((double)(end3 - start3) / CLOCKS_PER_SEC) + (randomSpeedBoost * 0.2);
					timer4 = ((double)(end4 - start4) / CLOCKS_PER_SEC) + (randomSpeedBoost * 0.2);
					
					//Show time Surviving
					SDL_Color textcolor = { 255,0,0 };
					string s = to_string(timer);
					s += "seconds";
					if (!gTextTexture.loadFromRenderedText(s, textcolor))
					{
						printf("Failed to render game timer");
					}
					//Show surviving high score
					string high = "Your Surviving Highest Time: " + to_string(survivehighscore);
					if (!gHighScoreText.loadFromRenderedText(high, textcolor))
					{
						printf("Failed to render game timer");
					}
					//Show Life Force
					string lifeFORCE = "Life: " + to_string(life);
					if (!gLife.loadFromRenderedText(lifeFORCE, textcolor))
					{
						printf("Failed to render game timer");
					}
					if (fullHEALTH == 1)
					{
						string fullHealth = "FULL HEALTH!!!";
						if (!gFHealth.loadFromRenderedText(fullHealth, textcolor))
						{
							printf("Failed to render game timer");
						}
					}
					
					//GameOver
					if (gameover == 1)
					{
						
						
						if (survivehighscore < timer)
						{
							ofstream finputscore("data/survivetime.txt");
							finputscore << timer << "\n";
						}
						quit = true;
					}
					

			


				}


			}

		}
		//Close SDL stuff
		//Close SDL stuff
		close();
		
		//Using Soil to view exit window
		quitSOILEX = 0;
		
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(900, 675);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("Game Over Screen");
		glutDisplayFunc(disDeath);
		glutIdleFunc(idleFunc);
		glutKeyboardFunc(keyFunc);
		myInitSOIL();
		glutMainLoop();
		//glutDestroyWindow(1);
			
		
		
	}
	;
	return 0;
}

