//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc, Vedaant Vyas
//Nov 17, 2021
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class character{
	//The X and Y offsets of the player
	int mPosX, mPosY;
	LTexture gPlayerTexture;

	//The velocity of the player
	int mVelX, mVelY;
    public:
        //The dimensions of the player
        static const int PLAYER_WIDTH = 80;
        static const int PLAYER_HEIGHT = 80;

        //Maximum axis velocity of the dot
        static const int PLAYER_VEL = 10;

        //Initializes the variables
        character(){
			//Initialize the offsets
			mPosX = 300;
			mPosY = 311;
			defaultX = mPosX;
			//Initialize the velocity
			mVelX = 0;
			mVelY = 0;
		}

        //Takes key presses and adjusts the player's velocity
        void handleEvent(SDL_Event& e){
			//If a key was pressed
			if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
				//Adjust the velocity
				switch(e.key.keysym.sym){
				case SDLK_UP: 
					mVelY -= PLAYER_VEL; 
					if(!gPlayerTexture.loadFromFile("images/player/playerUp.png")){
						printf("Failed to load player texture!\n");
					}
					break;
				case SDLK_DOWN: 
					mVelY += PLAYER_VEL;
					if(!gPlayerTexture.loadFromFile("images/player/playerDown.png")){
						printf("Failed to load player texture!\n");
					}
					break;
				case SDLK_LEFT: 
					mVelX -= PLAYER_VEL; 
					if(!gPlayerTexture.loadFromFile("images/player/playerLeft.png")){
						printf("Failed to load player texture!\n");
					}
					break;
				case SDLK_RIGHT: 
					mVelX += PLAYER_VEL; 
					if(!gPlayerTexture.loadFromFile("images/player/playerRight.png")){
						printf("Failed to load player texture!\n");
					}
					break;
				}
			}
			//If a key was released
			else if(e.type == SDL_KEYUP && e.key.repeat == 0){
				//Adjust the velocity
				switch (e.key.keysym.sym){
				case SDLK_UP: 
					mVelY += PLAYER_VEL; 
					break;
				case SDLK_DOWN: 
					mVelY -= PLAYER_VEL; 
					break;
				case SDLK_LEFT: 
					mVelX += PLAYER_VEL; 
					break;
				case SDLK_RIGHT: mVelX -= PLAYER_VEL;	
					break;
				}

			}
		}
		int defaultX;
        //Moves the player
        void move(){
			//Move the dot left or right
			mPosX += mVelX;

			//If the dot went too far to the left or right
			if((mPosX+10 < 0) || (mPosX+10 + PLAYER_WIDTH > SCREEN_WIDTH)){
				//Move back
				mPosX -= mVelX;
			}

			//Move the dot up or down
			mPosY += mVelY;

			//If the dot went too far up or down
			if((mPosY+10 < 0) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT)){
				//Move back
				mPosY -= mVelY;
			}
		}
		//friend BadCloud;
        //Shows the player on the screen
        void render();
		//Get the position of character in x direction
		int getXPOSC(){
			return mPosX;
		}
		//Get the position of character in y direction
		int getYPOSC(){
			return mPosY;
		}
		//void detectingCLOUDATTACK(BadCloud&ref);
};