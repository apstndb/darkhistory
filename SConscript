env = Environment( CPPDEFINES=['_UNICODE'], CPPPATH="/usr/include/freetype2" )
Import( 'tools' )
Tool( tools )(env)
commonlibs = Split( 'glfw' )
cppflags = Split( '-Wall -pedantic -Os -march=i686' )
#cppflags = Split( '-Wall -pedantic -g' )
#cppflags = Split('')
lib = {}
lib['crossmingw'] = commonlibs + Split( 'opengl32 glu32 glc32')
lib['gcc'] = commonlibs + Split( 'GLU GLC' )
commonsrc = Split( 'darkhistory.cpp game.cpp mylib.cpp mygllib.cpp kanaset.cpp' )
src = {}
src['crossmingw'] = commonsrc + Split('windows.cpp')
src['gcc'] = commonsrc + Split('main.cpp')
ldflags = {}
ldflags['crossmingw'] = Split( '-Wl,--subsystem,windows' )
ldflags['gcc'] = Split( '' )
env . Program( 'darkhistory', src[tools], CPPFLAGS=cppflags, LIBS=lib[tools], LINKFLAGS=ldflags[tools])
