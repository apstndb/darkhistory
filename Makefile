LDLIBS = -lglfw -lGLU -lftgl
CPPFLAGS = -g `freetype-config --cflags`
darkhistory: darkhistory.o mylib.o
