#include "objects/character.h"
#include "objects/cloud.h"
#include "death.cpp"
//#include "oHNO3.cpp"

void detectingCLOUD(BadCloud&BC, character& ch)
{
	int cloudPOSX, cloudPOSY;
	cloudPOSX = BC.getXPOS();
	cloudPOSY = BC.getYPOS();
	int gameover;
	int posPlayerX = ch.getXPOSC();
	int posPlayerY = ch.getYPOSC();
	//printf("%d ", posPlayerY);
	//printf("%d", cloudPOSY);
	if (BC.attackIND == 2)
	{
		if ((cloudPOSX < posPlayerX && cloudPOSX + BC.CLOUD_WIDTH > posPlayerX&& posPlayerY > cloudPOSY + BC.CLOUD_HEIGHT))
		{
			gameover = true; //call the death cpp
			printf("%d", gameover);
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