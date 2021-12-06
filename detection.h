//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc Vedaant Vyas
//Nov 29, 2021
#include "death.cpp"
#include "objects/powerup.h"
#include "global.h"

void detectingCLOUD(BadCloud&BC, character& ch){
	int cloudPOSX, cloudPOSY;
	cloudPOSX = BC.getXPOS();
	cloudPOSY = BC.getYPOS();
	int posPlayerX = ch.getXPOSC();
	int posPlayerY = ch.getYPOSC();

	if(BC.attackIND == 2){		

		if((cloudPOSX < posPlayerX && cloudPOSX + BC.CLOUD_WIDTH > posPlayerX&& posPlayerY > cloudPOSY + BC.CLOUD_HEIGHT-100)){
			if(ch.getLife() > 0){
				if(ch.getShield() > 0){
					ch.dmgShield();
				}
				else{
					ch.damage();
				}
			}
			else{
				gameover = true;
			}
		}
		else{
			gameover = false;
		}
	}
}
void detectionPOWERUP(powerup& pu, character& player){
	int xpospu = pu.getXPOS();
	int ypospu = pu.getYPOS();
	int xpospl = player.getXPOSC();
	int ypospl = player.getYPOSC();

	if((ypospl + 20 > ypospu && ypospl + 20 < ypospu + pu.POWERUP_HEIGHT) && (xpospl + 20 > xpospu && xpospl + 20 < xpospu + pu.POWERUP_WIDTH)){
		player.addShield();
		pu.~powerup();
	}
} 
