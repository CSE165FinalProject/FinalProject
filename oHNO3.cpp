//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc Vedaant Vyas
//Nov 17, 2021
#include <SDL2/SDL.h> //SDL2 installed libraries 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <SOIL/SOIL.h> //SOIL installed library 

#include <GL/glut.h> //glut installed library

#include <fstream> //standard c++ library 

using namespace std;

extern const int SCREEN_WIDTH = 1200; //Screen dimension constants
extern const int SCREEN_HEIGHT = 800;
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

bool init(); //Starts up SDL and creates window
void close(); //Frees media and shuts down SDL

#include "objects/character.h" //included .h files 
#include "objects/cloud.h"
#include "detection.h"
#include "global.h"
#include "game.cpp"

int main(int argc, char* argv[]){
	tryAgain = false;
	bool replay = true;
	powerupLifetime = 0;
	
	while(!tryAgain){ 
		while(replay){
			if(!init()){//Start up SDL and create window
				printf("Failed to initialize!\n");
			}
			else{
				if (!loadMedia()){ //Load media
					printf("Failed to load media!\n");
				}
				else{
					quit = false; //Main loop flag
					ifstream fgetdata("data/survivetime.txt"); //getting Highscore
					fgetdata >> survivehighscore;
					fgetdata.close();
					
					time_t start, end; //Initializing time for diff clouds
					time_t start1 = 0, end1 = 0;
					time_t start2 = 0, end2 = 0;
					time_t start3 = 0, end3 = 0;
					time_t start4 = 0, end4 = 0;
					start = clock();
					
					SDL_Event e; //Event handler

					character player; //Declare the class objects
					BadCloud BCImage[4];
					powerup powerups;

					while(!quit){ //While application is running
						while (SDL_PollEvent(&e) != 0){ //Handle events on queue
							if(e.type == SDL_QUIT){ //User requests quit
								quit = true;
							}
							player.handleEvent(e); //Handle input for the player
						}

						player.move(); //Move the Player

						
						if(timer % 20 <= 5 && timerStarted1 == 0){ //Start Timer at diff. instances for diff. clouds
							start1 = clock();
							timerStarted1 = 1;
						}
						else if(timer % 20 > 5 && timer % 20 <= 10 && timerStarted2 == 0){
							start2 = clock();
							timerStarted2 = 1;
						}
						else if(timer % 20 > 10 && timer % 20 <= 15 && timerStarted3 == 0){
							start3 = clock();
							timerStarted3 = 1;
						}
						else if(timer % 20 > 15 && timer % 20 <= 20 && timerStarted4 == 0){
							start4 = clock();
							timerStarted4 = 1;
						}

						BCImage[0].moveBC(); //Cloud Move
						BCImage[1].moveBC();
						BCImage[2].moveBC();
						BCImage[3].moveBC();

						//Clear screen
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						
						//Change Background overtime
						if(timer > 40){
							gBGTextureLater2.render(0, 0);
						}
						else if(timer > 20){
							gBGTextureLater.render(0, 0);
						}
						else{
							gBGTexture.render(0, 0);
						}

						//Detecting objects
						detectingCLOUD(BCImage[0], player);
						detectingCLOUD(BCImage[1], player);
						detectingCLOUD(BCImage[2], player);
						detectingCLOUD(BCImage[3], player);
						
						
						player.render(); //Render player
						powerups.spawn(); //Pick random coordinates for powerup
						powerups.render(); //Render powerups
						
						//if timer started for each cloud, render and start attacking phase
						if(timerStarted1 == 1){
							end1 = clock();
							BCImage[0].attack(BCImage[0], player);
							BCImage[0].render(BCImage[0].attackIND);
						}
						if(timerStarted2 == 1){
							end2 = clock();
							BCImage[1].attack(BCImage[1], player);
							BCImage[1].render(BCImage[1].attackIND);
						}
						if(timerStarted3 == 1){
							end3 = clock();
							BCImage[2].attack(BCImage[2], player);
							BCImage[2].render(BCImage[2].attackIND);
						}
						if(timerStarted4 == 1){
							end4 = clock();
							BCImage[3].attack(BCImage[3], player);
							BCImage[3].render(BCImage[3].attackIND);
						}

						
						detectionPOWERUP(powerups, player); //Detect powerup if player touches
						
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
						SDL_Color textcolor = {255, 0, 0};
						string s = to_string(timer);
						s += "seconds";
						if(!gTextTexture.loadFromRenderedText(s, textcolor)){
							printf("Failed to render game timer");
						}
						//Show surviving high score
						string high = "Your Surviving Highest Time: " + to_string(survivehighscore);
						if(!gHighScoreText.loadFromRenderedText(high, textcolor)){
							printf("Failed to render game timer");
						}
						//Show Life Force
						string lifeFORCE = "Life: " + to_string(life);
						if(!gLife.loadFromRenderedText(lifeFORCE, textcolor)){
							printf("Failed to render game timer");
						}
						if(fullHEALTH == 1){
							string fullHealth = "FULL HEALTH!!!";
							if (!gFHealth.loadFromRenderedText(fullHealth, textcolor)){
								printf("Failed to render game timer");
							}
						}
						
						//GameOver
						if(gameover == 1){

							if(survivehighscore < timer){
								ofstream finputscore("data/survivetime.txt");
								finputscore << timer << "\n";
							}
							quit = true;
						}
					}
				}
			}
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
	}
	return 0;
}

