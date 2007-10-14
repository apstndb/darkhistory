LDLIBS = -lglfw -lGLU -lftgl
CPPFLAGS = -Wall -pedantic -g `freetype-config --cflags`
all: darkhistory mytest
darkhistory: darkhistory.o mylib.o mygllib.o
mytest: mytest.o mylib.o
