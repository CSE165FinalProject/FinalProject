//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc Vedaant Vyas
//Nov 29, 2021
#include "death.cpp"
#include "objects/powerup.h"
extern int gameover;
extern int life;
extern int fullHEALTH;

void detectingCLOUD(BadCloud&BC, character& ch){
	int cloudPOSX, cloudPOSY;
	cloudPOSX = BC.getXPOS();
	cloudPOSY = BC.getYPOS();
	int posPlayerX = ch.getXPOSC();
	int posPlayerY = ch.getYPOSC();

	if(BC.attackIND == 2){		

		if((cloudPOSX < posPlayerX && cloudPOSX + BC.CLOUD_WIDTH > posPlayerX&& posPlayerY > cloudPOSY + BC.CLOUD_HEIGHT-100)){
			if (life > 0){
				life--;
			}
			else{
				gameover = true;
			}
			//gameover = true;
			 //call the death cpp
			//printf("%d", gameover);
			//death();
		}
		else{
			gameover = false;
			//printf("%d", gameover);
		}
	}
	//if(cloudPOS < posPlayer && cloudPOS + BC.CLOUD_WIDTH > posPlayer){
	//	gameover = true; //call the death cpp
	//	printf("%d", gameover);
	//	//death();
	//}
	//else{
	//	gameover = false;
	//	//printf("%d", gameover);
	//}
}
void detectionPOWERUP(powerup& pu, character& player){
	int xpospu = pu.getXPOS();
	int ypospu = pu.getYPOS();
	int xpospl = player.getXPOSC();
	int ypospl = player.getYPOSC();

	if((ypospl+20 > ypospu && ypospl+20 < ypospu + pu.POWERUP_HEIGHT) && (xpospl + 20 > xpospu && xpospl + 20 < xpospu + pu.POWERUP_WIDTH)){
			if(life < 20){
				life++;
			}
			else{
				fullHEALTH = 1;
			}
	}
	else{
		fullHEALTH = 0;
	}
} 
