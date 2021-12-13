CC = g++

gamefile = oHNO3.cpp

ifdef OS
   	exe = oHNO3win.exe

   	comp = -Wall -DUSEGLEW -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -mwindows -lfreeglut -lglew32 -lglu32 -lSOIL -lopengl32 -lm -o
else
   	ifeq ($(shell uname), Linux)
      	exe = oHNO3.exe 

	  	comp = -Wall -DUSEGLEW -lglut -lGLU -lGL -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSOIL -lm -o
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

clean: #only cleans in linux
	rm -f oHNO3win.exe oHNO3.exe 
