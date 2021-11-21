//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc add names guys
//Nov 17, 2021
#include <GL/glut.h>

using namespace std; 

#include "title.cpp"

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 675);
    glutInitWindowPosition(0, 0);  
    glutCreateWindow("oHNO3");


    return 0;
}