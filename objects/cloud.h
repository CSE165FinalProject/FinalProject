//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, add names guys
//Nov 17, 2021
#ifndef CLOUD_FILE_H
#define CLOUD_FILE_H 
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
//#include "sdlcreatewindow.cpp"
//#include <createSDLWIN.h>
//#include "imageloader.cpp"
extern int timer,timer1, timer2, timer3, timer4;
extern int timerStarted1, timerStarted2, timerStarted3, timerStarted4;
#include "objects/character.h"
//#include "oHNO3.cpp"
class BadCloud
{
    public:
        //The dimensions of the Cloud
        static const int CLOUD_WIDTH = 190;
        static const int CLOUD_HEIGHT = 160;

        //Maximum axis velocity of the Cloud
		static int CLOUD_VEL;
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
		//Get Y position of the cloud
		int getYPOS();
		//Switching between good and bad cloud
		void attack(BadCloud&Cloud,character & player);
		//int getYPOS();
    private:
        //The X and Y offsets of the cloud
        int mPosX, mPosY;
		//Number of Clouds
		static int numCLOUDS;
		static int numAttack;
		int id;
		//int numAttack;
        //The velocity of the Cloud
        int mVelX, mVelY;
};
int BadCloud::getYPOS()
{
	return mPosY;
}
int BadCloud::numCLOUDS = 0;
int BadCloud::numAttack = 0;
int BadCloud::CLOUD_VEL = 6;
void BadCloud::attack(BadCloud& Cloud, character& player)
{
	//int startIT;
	static double leaveONEgood = 3;
	
	//printf("%d\n", randomCLOUDSPAWNDAMAGE);
	//printf("%d\n", leaveONEgood);
	//printf("%d\n", Cloud.id);
	//printf("%d\n", timer1);
	if (timerStarted1 == 1&& Cloud.id == 0)
	{
		if (timer1 % 20 > 12 && timer1 % 20 < 16)
		{
			
			Cloud.attackIND = 1;
			
		}
		else if (timer1 % 20 >= 16 && timer1 % 20 < 20) {
			if (Cloud.attackIND == 1)
			{
				Cloud.attackIND = 2;
			}
			//leaveONEgood = 0;
			//Cloud.attackIND = 2;
		}
		else
		{
			
			Cloud.attackIND = 0;
		}
	}
	if (timerStarted2 == 1&&Cloud.id == 1)
	{
		if (timer2 % 20 > 12 && timer2 % 20 < 16)
		{
			
			Cloud.attackIND = 1;
			
		}
		else if (timer2 % 20 >= 16 && timer2 % 20 < 20) {
			if (Cloud.attackIND == 1)
			{
				Cloud.attackIND = 2;
			}
			//leaveONEgood = 0;
			//Cloud.attackIND = 2;
		}
		else
		{

			Cloud.attackIND = 0;
		}
	}
	
	if (timerStarted3 == 1 && Cloud.id == 2)
	{
		if (timer3 % 20 > 12 && timer3 % 20 < 16)
		{
			
			Cloud.attackIND = 1;
			
		}
		else if (timer3 % 20 >= 16 && timer3 % 20 < 20) {
			if (Cloud.attackIND == 1)
			{
				Cloud.attackIND = 2;
			}
			//leaveONEgood = 0;
			//Cloud.attackIND = 2;
		}
		else
		{
			if (Cloud.attackIND != 1)
			{
				Cloud.attackIND = 0;
			}
			//Cloud.attackIND = 0;
		}

	}
	if (timerStarted4 == 1 && Cloud.id == 3)
	{
		if (timer4 % 20 > 12 && timer4 % 20 < 16)
		{
			
			Cloud.attackIND = 1;
			
		}
		else if (timer4 % 20 >= 16 && timer4 % 20 < 20) {
			if (Cloud.attackIND == 1)
			{
				Cloud.attackIND = 2;
			}
			//leaveONEgood = 0;
			//Cloud.attackIND = 2;
		}
		else
		{

			Cloud.attackIND = 0;
		}
	}
	
	
	
}
int BadCloud::getXPOS()
{
	return mPosX;
}
BadCloud::BadCloud()
{
	//initialize position
	mPosY= -140 +  numCLOUDS*150;
	mPosX = numCLOUDS *150;
	/*mPosY = 0;
	mPosX = 0;*/
	//direction of cloud
	directionofCLOUD = 0;

	//attack
	attackIND = 0;

	//Initialize the velocity
	mVelX = CLOUD_VEL;
	mVelY = 0;

	//Number of Attacking Clouds
	//numAttack = 0;
	
	//Id of cloud
	id = numCLOUDS;

	//count the clouds present
	numCLOUDS++;
}
void BadCloud::moveBC()
{
	//move to the right
	if (timer % 2 == 0)
	{
		CLOUD_VEL += 10;
	}
	if (directionofCLOUD == 0)
	{
		mPosX += mVelX;

		//If the Cloud went too far to the left or right
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

#endif