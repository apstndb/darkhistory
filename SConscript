#env = Environment( CPPDEFINES=Split('_STLP_DEBUG _UNICODE'), CPPPATH=Split('/usr/include/stlport /usr/include/freetype2') )
env = Environment( CPPDEFINES=Split('_UNICODE'), CPPPATH=Split('/usr/include/freetype2') )
Import( 'tools' )
Tool( tools )(env)
commonlibs = Split( 'glfw' )
ccflags = Split( '-Wall -pedantic -Os -march=i686' )
#ccflags = Split( '-Wall -pedantic -g -std=c++98' )
#ccflags = Split( '-Wall -pg -g --coverage' )
#cppflags = Split('')
include = {}
include['crossmingw'] = Split( '')
include['gcc'] = Split( '/usr/include/stlport' )
lib = {}
lib['crossmingw'] = commonlibs + Split( 'opengl32 glu32 glc32')
#lib['gcc'] = commonlibs + Split( 'GLU GLC stlportstlg gcov' )
lib['gcc'] = commonlibs + Split( 'GLU GLC' )
commonsrc = Split( 'main.cpp darkhistory.cpp game.cpp mylib.cpp mygllib.cpp kanaset.cpp input.cpp' )
src = {}
src['crossmingw'] = commonsrc + Split('')
src['gcc'] = commonsrc + Split('')
ldflags = {}
ldflags['crossmingw'] = Split( '-Wl,--subsystem,windows' )
ldflags['gcc'] = Split( '' )
env . Program( 'darkhistory', src[tools], CCFLAGS=ccflags, LIBS=lib[tools], LINKFLAGS=ldflags[tools], INCLUDE=include[tools])
