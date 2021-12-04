//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc, Vedaant Vyas
//Nov 17, 2021
#include "death.cpp"
//#include "objects/LTexture.h"

GLuint death; //Textures
LTexture gPlayerTexture;
LTexture gBGTexture;
LTexture gBadCloudTexture;
LTexture gGoodCloudTexture;
LTexture gAcidCloudTexture;
LTexture gBGTextureLater;
LTexture gTextTexture;
LTexture gHighScoreText;
LTexture gPowerUp;
LTexture gLife;
LTexture gFHealth;

TTF_Font* gFont = NULL; //Font

void powerup::render(){ //render powerup
	gPowerUp.render(mPosX, mPosY); //show powerup
}

void character::render(){ //render player
	gPlayerTexture.render(mPosX, mPosY); //Show the player
}

void BadCloud::render(int attack){ //render cloud
	
	if(attack == 0){
		gGoodCloudTexture.render(mPosX, mPosY); //show the cloud
		//gGoodCloudTexture.render(mPosX + 300, mPosY);
	}
	else if(attack == 1){ //render bad cloud
		gBadCloudTexture.render(mPosX, mPosY); //show bad cloud
		//gBadCloudTexture.render(mPosX + 300, mPosY);
	}
	else{
		gAcidCloudTexture.render(mPosX, mPosY);
	}
	//gbadcloudtexture.render(mposx, mposy);
}
void loadTextures(){
	death = SOIL_load_OGL_texture(
		"images/go.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}
void loadTEXTTEXTURES(){
	//load text
	//printf("%d\n", timer);
	//gTextTexture.render(((SCREEN_WIDTH - gTextTexture.getWidth()) / 2), (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
	gTextTexture.render(0, 0);
	gHighScoreText.render(SCREEN_WIDTH - gHighScoreText.getWidth(), 0);
	gLife.render(400, 0);
	gFHealth.render(0, 600);
}
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Acid Rain Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize ttf
				if(TTF_Init() == -1){
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
//Display death screen using glut and soil
void disDeath(){
	//display death screen
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, death);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(640, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(640, 480);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 480);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Display Surviving Time
	string ST = "Surviving Time: ";
	ST += to_string(timer);
	int len = ST.size();
	glRasterPos2f(300, 260);
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ST[i]);
	}

	//Display Highest Surviving Time
	string SHT = "Surviving Highest Time: ";
	SHT += to_string(survivehighscore);
	int len1 = SHT.size();
	glRasterPos2f( 300, 240);
	for(int i = 0; i < len1; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, SHT[i]);
	}
	if(timer > survivehighscore){
		//display acknowledgement of new high score
		string congratuation = "NEW HIGHSCORE!!";
		int len2 = congratuation.size();
		glRasterPos2f(300, 220);
		for(int i = 0; i < len2; i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, congratuation[i]);
		}
	}
	glFlush();

}
void close(){
	//Free loaded images
	gPlayerTexture.free();
	gBGTexture.free();
	gBadCloudTexture.free();
	gGoodCloudTexture.free();
	gTextTexture.free();
	gPowerUp.free();
	
	//Font
	TTF_CloseFont(gFont);
	gFont = NULL;
	
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
//if you want to initialize something in soil
void initializeSOIL(){
	//initialize soil variables
}
//Soil init function
void myInitSOIL(){
	//startup SOIL
	glClearColor(1.0, 4.0, 6.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	loadTextures();
	initializeSOIL();
}
//Glut Idle
void idleFunc(){
	//idle 
	glutPostRedisplay();
}
bool loadMedia(){
	//Loading success flag
	bool success = true;
	//Load powerup texture
	if(!gPowerUp.loadFromFile("images/powerup.png")){
		printf("Failed to load powerup texture!\n");
		success = false;
	}
	//Load player texture
	if(!gPlayerTexture.loadFromFile("images/player/playerUp.png")){
		printf("Failed to load player texture!\n");
		success = false;
	}
	//Load background texture
	if(!gBGTexture.loadFromFile("images/goodland.jpg")){
		printf("Failed to load good background texture!\n");
		success = false;
	}
	//Load background texture
	if(!gBGTextureLater.loadFromFile("images/damageland.jpg")){
		printf("Failed to load bad background texture!\n");
		success = false;
	}
	//Loud Warning Cloud
	if(!gBadCloudTexture.loadFromFile("images/badcloud.png")){
		printf("Failed to load Warning cloud texture!\n");
		success = false;
	}
	//Load good cloud
	if(!gGoodCloudTexture.loadFromFile("images/goodcloud.png")){
		printf("Failed to load goodcloud texture!\n");
		success = false;
	}
	//load acid cloud
	if(!gAcidCloudTexture.loadFromFile("images/acidrain.png")){
		printf("Failed to load acid rain texture!\n");
		success = false;
	}
	
	//load font
	gFont = TTF_OpenFont("images/gameFONT.ttf",20);
	if(gFont == NULL){
		printf("Failed to load font: %s\n", TTF_GetError());
		success = false;
	}
	else{
		SDL_Color textcolor = { 0,0,0 };
		string s = to_string(timer);
		if(!gTextTexture.loadFromRenderedText(s, textcolor)){
			printf("Failed to render game timer");
			success = false;
		}
	}
	return success;
}
//void glutLeaveMainLoop(void);
void keyFunc(unsigned char k, int x, int y){
	//end screen keyboard input
	if(k == 'n' || k == 'N'){
		//printf("Hello");
		/*initializeSOIL();
		glutPostRedisplay();*/
		tryAgain = false;
		printf("%d", tryAgain);
		quitSOILEX = true;
		//init();	
	}
	else if (k == 'm' || k == 'M'){
		tryAgain = true;
		quitSOILEX = true;
	}
}
