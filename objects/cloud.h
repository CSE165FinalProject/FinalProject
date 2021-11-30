//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, add names guys
//Nov 17, 2021
#ifndef CLOUD_FILE_H
#define CLOUD_FILE_H 
#include <SDL.h>
#include <SDL_image.h>
//#include "sdlcreatewindow.cpp"
//#include <createSDLWIN.h>
//#include "imageloader.cpp"
extern int timer;
#include "objects/character.h"
//#include "oHNO3.cpp"
class BadCloud
{
    public:
        //The dimensions of the Cloud
        static const int CLOUD_WIDTH = 45;
        static const int CLOUD_HEIGHT = 24;

        //Maximum axis velocity of the Cloud
        static const int CLOUD_VEL = 6;
        //Motion of the cloud left to right and vice version
        //void movementBADCLOUD();
        //Initializes the variables
        BadCloud();
        int directionofCLOUD;
        int attackIND;
        //Takes key presses and adjusts the Cloud's velocity

        //Moves the Cloud
        void moveBC();

        //Shows the Cloud on the screen
        void render(int attack);

		//friend character;
		//Get X Position of the cloud
		int getXPOS();
		//Switching between good and bad cloud
		void attack(BadCloud&Cloud,character & player);
		//int getYPOS();
    private:
        //The X and Y offsets of the cloud
        int mPosX, mPosY;

        //The velocity of the Cloud
        int mVelX, mVelY;
};

void BadCloud::attack(BadCloud& Cloud, character& player)
{
	if (timer % 10 > 5)
	{
		Cloud.attackIND = 1;
	}
	else
	{
		Cloud.attackIND = 0;
	}
}
int BadCloud::getXPOS()
{
	return mPosX;
}
BadCloud::BadCloud()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;
	directionofCLOUD = 0;
	attackIND = 0;
	//Initialize the velocity
	mVelX = CLOUD_VEL;
	mVelY = 0;
}
void BadCloud::moveBC()
{
		//move to the right
	if (directionofCLOUD == 0)
	{
		mPosX += mVelX;

		//If the dot went too far to the left or right
		if (mPosX + CLOUD_WIDTH > SCREEN_WIDTH)
		{
			//Move back
			mPosX -= mVelX;
			directionofCLOUD = 1;
		}

	}
	else if(directionofCLOUD == 1)
	{
		mPosX -= mVelX;
		if (mPosX < 0)
		{
			//Move back
			mPosX -= mVelX;
			directionofCLOUD = 0;
		}
	}	
	
}
//void BadCloud::render()
//{
//	//Show the Cloud
//	gBadCloudTexture.render(mPosX, mPosY);
//}
#endif