CC = g++ 

ifdef OS
   exe = oHNO3win.exe
else
   ifeq ($(shell uname), Linux)
      exe = oHNO3.exe 
   endif
endif

all:
	$(CC) OpenGL.cpp -lglut -lGL -lGLEW -lGLU -o $(exe) 

debug: 
	g++ -g OpenGL.cpp -o broken

debugtest: 
	gdb broken

run: 
	./$(exe)

clean:
	rm -f $(exe)