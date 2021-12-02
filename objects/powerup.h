#ifndef powerup_H
#define powerup_H

//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, add names guys
//Nov 17, 2021

#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
//#include "sdlcreatewindow.cpp"
//#include <createSDLWIN.h>
//#include "imageloader.cpp"
extern int timer,timer1, timer2, timer3, timer4;
extern int timerStarted1, timerStarted2, timerStarted3, timerStarted4;

//#include "oHNO3.cpp"
class powerup
{
    public:
        //The dimensions of the Power up
        static const int POWERUP_WIDTH = 100;
        static const int POWERUP_HEIGHT = 100;

        //Maximum axis velocity of the Cloud
        static const int CLOUD_VEL = 6;
        //Motion of the cloud left to right and vice version
        //void movementBADCLOUD();
        //Initializes the variables
        powerup();

        //Shows the Cloud on the screen
       // void render();

		//friend character;
		//Get X Position of the cloud
		int getXPOS();
		//Get Y position of the cloud
		int getYPOS();
		//Switching between good and bad cloud
		
        //Spawn Powerup
        void spawn();
        //Render powerup
        void render();
		//int getYPOS();
    private:
        //The X and Y offsets of the cloud
        int mPosX, mPosY;
		
		
		//int id;
		//int numAttack;
        //The velocity of the Cloud
        int mVelX, mVelY;
};
powerup::powerup()
{
    mPosX = 0;
    mPosY = 0;
    mVelX = 0;
    mVelY = 0;
}
int powerup::getYPOS()
{
	return mPosY;
}
int powerup::getXPOS()
{
    return mPosX;
}

void powerup::spawn()
{
    srand(time(NULL));
    int xspawncoords = rand() % 700 + 1;
    int yspawncoords = rand() % 400 + 1;
    mPosX = xspawncoords;
    mPosY = yspawncoords;

}
#endif
