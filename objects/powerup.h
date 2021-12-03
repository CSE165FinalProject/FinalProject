//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, add names guys
//Nov 17, 2021
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "../global.h"

class powerup{
    //The X and Y offsets of the cloud
    int mPosX, mPosY;
    int mVelX, mVelY;

    public:
        //The dimensions of the Power up
        static const int POWERUP_WIDTH = 100;
        static const int POWERUP_HEIGHT = 100;

        //Maximum axis velocity of the Power up
        static const int CLOUD_VEL = 6;
        //Motion of the cloud left to right and vice version
    
        //Initializes the variables
        powerup(){
            //Initialize coordinates and velocity
            mPosX = 0;
            mPosY = 0;
            mVelX = 0;
            mVelY = 0;
        }

        //Shows the Power up on the screen
       // void render();

		//friend character;
		//Get X Position of the powerup
		int getXPOS(){
            //Get X position of object
            return mPosX;
        }
		//Get Y position of the powerup
		int getYPOS(){
            //Get X position of object
            return mPosY;
        }

        //Spawn Powerup
        void spawn(){
            //Get random coordinates;
            srand(time(NULL));
            int xspawncoords = rand() % 800 + 1;
            int yspawncoords = rand() % 400 + 1;
            mPosX = xspawncoords;
            mPosY = yspawncoords;

            return; 
        }
        //Render powerup
        void render();
};


