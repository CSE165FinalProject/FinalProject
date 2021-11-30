#include "objects/character.h"
#include "objects/cloud.h"
#include "death.cpp"
//#include "oHNO3.cpp"

void detectingCLOUD(BadCloud&BC,character&ch)
{
	int cloudPOS;
	cloudPOS = BC.getXPOS();
	int gameover;
	int posPlayer = ch.getXPOSC();
	if (cloudPOS < posPlayer && cloudPOS + BC.CLOUD_WIDTH > posPlayer)
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