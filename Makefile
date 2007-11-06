LDLIBS = -lstdc++ -lglfw -lGLU -lftgl
CPPFLAGS = -Wall -pedantic -g `freetype-config --cflags`
all: darkhistory mytest
darkhistory: darkhistory.o mylib.o mygllib.o
mytest: mytest.o mylib.o
main: main.o mylib.o
test: test.o mylib.o
clean:
	rm -f *.o test mytest darkhistory
