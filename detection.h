#include "objects/character.h"
#include "objects/cloud.h"
#include "death.cpp"
#include "objects/powerup.h";
//#include "oHNO3.cpp"
extern int gameover;
extern int life;
extern int fullHEALTH;
void detectingCLOUD(BadCloud&BC, character& ch)
{
	int cloudPOSX, cloudPOSY;
	cloudPOSX = BC.getXPOS();
	cloudPOSY = BC.getYPOS();
	//int gameover;
	int posPlayerX = ch.getXPOSC();
	int posPlayerY = ch.getYPOSC();
	//printf("%d %d\n", cloudPOSX, cloudPOSY);
	//printf("%d", cloudPOSY);
	if (BC.attackIND == 2)
	{		

		if ((cloudPOSX < posPlayerX && cloudPOSX + BC.CLOUD_WIDTH > posPlayerX&& posPlayerY > cloudPOSY + BC.CLOUD_HEIGHT-100))
		{
			//gameover = true;
			if (life > 0)
			{
				life--;
			}
			else
			{
				gameover = true;
			}
			//gameover = true;
			 //call the death cpp
			//printf("%d", gameover);
			//death();
		}
		else
		{
			gameover = false;
			//printf("%d", gameover);
		}
	}
	//if (cloudPOS < posPlayer && cloudPOS + BC.CLOUD_WIDTH > posPlayer)
	//{
	//	gameover = true; //call the death cpp
	//	printf("%d", gameover);
	//	//death();
	//}
	//else
	//{
	//	gameover = false;
	//	//printf("%d", gameover);
	//}
}
void detectionPOWERUP(powerup&pu, character&player)
{
	int xpospu = pu.getXPOS();
	int ypospu = pu.getYPOS();
	int xpospl = player.getXPOSC();
	//printf(" %d %d\n", xpospu, ypospu);
	int ypospl = player.getYPOSC();
	//printf(" %d %d |  %d %d\n", xpospl, ypospl, xpospu,ypospu);

	if ((ypospl+20 > ypospu && ypospl+20 < ypospu + pu.POWERUP_HEIGHT) && (xpospl + 20 > xpospu && xpospl + 20 < xpospu + pu.POWERUP_WIDTH))
	{
			if (life < 20)
			{
				life++;
			}
			else
			{
				fullHEALTH = 1;
			}
	}
	else
	{
		fullHEALTH = 0;
	}
} 
