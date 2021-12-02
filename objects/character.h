//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc, Vedaant Vyas
//Nov 17, 2021
#ifndef CHARACTER_FILE_H
#define CHARACTER_FILE_H
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
//#include "imageloader.cpp"
#include <SDL.h>
#include <SDL_image.h>


class character
{
    public:
        //The dimensions of the player
        static const int PLAYER_WIDTH = 100;
        static const int PLAYER_HEIGHT = 100;

        //Maximum axis velocity of the dot
        static const int PLAYER_VEL = 10;

        //Initializes the variables
        character();

        //Takes key presses and adjusts the player's velocity
        void handleEvent(SDL_Event&e);
		int defaultX;
        //Moves the player
        void move();
		//friend BadCloud;
        //Shows the player on the screen
        void render();
		//Get the position of character in x direction
		int getXPOSC();
		//Get the position of character in y direction
		int getYPOSC();
		//void detectingCLOUDATTACK(BadCloud&ref);
    private:
        //The X and Y offsets of the player
        int mPosX, mPosY;

        //The velocity of the player
        int mVelX, mVelY;
};
int character::getYPOSC()
{
	return mPosY;
}
int character::getXPOSC()
{
	return mPosX;
}
character::character()
{
	//Initialize the offsets
	mPosX = 300;
	mPosY = 311;
	defaultX = mPosX;
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void character::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= PLAYER_VEL; break;
		case SDLK_DOWN: mVelY += PLAYER_VEL; break;
		case SDLK_LEFT: mVelX -= PLAYER_VEL; break;
		case SDLK_RIGHT: mVelX += PLAYER_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += PLAYER_VEL; break;
		case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
		case SDLK_LEFT: mVelX += PLAYER_VEL; break;
		case SDLK_RIGHT: mVelX -= PLAYER_VEL; break;
		}

	}
}
void character::move()
{
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + PLAYER_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY;
	}
}

#endif