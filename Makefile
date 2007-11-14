LDLIBS = -lstdc++ -lglfw -lGLU -lftgl
CPPFLAGS = -Wall -pedantic -g `freetype-config --cflags`
all: darkhistory main
darkhistory: darkhistory.o mylib.o mygllib.o 
//mytest: mytest.o mylib.o
main: main.o mylib.o mygllib.o kanaset.o
//test: test.o mylib.o
clean:
	rm -f *.o test mytest darkhistory
main.o: main.cpp mylib.h input.hpp kanaset.hpp
darkhistory.o: darkhistory.cpp mylib.h mygllib.h
mylib.o: mylib.cpp mylib.h
mygllib.o: mygllib.cpp mygllib.h
kanaset.o: kanaset.cpp kanaset.hpp
# DO NOT DELETE
