CC = g++

gamefile = oHNO3.cpp
testfile = opengl.cpp


ifdef OS
   exe = oHNO3win.exe
   testexe = openglwin.exe

   comp = -Wall -DUSEGLEW -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -mwindows -lfreeglut -lglew32 -lglu32 -lSOIL -lopengl32 -lm -o
else
   ifeq ($(shell uname), Linux)
      exe = oHNO3.exe 
	  testexe = opengl.exe

	  comp = -lglut -lGL -lGLEW -lGLU -lSDL -lSDL_mixer -lSOIL -o
   endif
endif

all:
	$(CC) $(gamefile) $(comp) $(exe) 

test:
	$(CC) $(testfile) $(comp) $(testexe)

debug: 
	g++ -g OpenGL.cpp -o broken

debugtest: 
	gdb broken

run: 
	./$(exe)

runtest: 
	./$(testexe)

clean:
	rm -f oHNO3win.exe oHNO3.exe openglwin.exe opengl.exe