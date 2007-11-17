LDLIBS = -lstdc++ -lglfw -lGLU -lftgl
CFLAGS = -Wall -pedantic -g `freetype-config --cflags`
CXXFLAGS = $(CFLAGS)
all: darkhistory main
darkhistory: darkhistory.o mylib.o mygllib.o 
#mytest: mytest.o mylib.o
main: main.o mylib.o mygllib.o kanaset.o game.o
#test: test.o mylib.o
clean:
	rm -f *.o test mytest darkhistory main
main.o: main.cpp mylib.h input.hpp kanaset.hpp game.hpp
darkhistory.o: darkhistory.cpp mylib.h mygllib.h
mylib.o: mylib.cpp mylib.h
mygllib.o: mygllib.cpp mygllib.h
kanaset.o: kanaset.cpp kanaset.hpp mylib.h
game.o: game.cpp game.hpp
