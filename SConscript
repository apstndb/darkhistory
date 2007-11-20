#Import( 'expenv' )
env = Environment( CPPDEFINES=['_UNICODE'], CPPPATH="/usr/include/freetype2" )
Import( 'tools' )
#env = expenv
Tool( tools )(env)
commonlibs = Split( 'glfw ftgl boost_filesystem' )
lib = {}
lib['crossmingw'] = commonlibs + Split( 'opengl32 glu32')
lib['gcc'] = commonlibs + Split( 'GLU' )
commonsrc = Split( 'darkhistory.cpp game.cpp mylib.cpp mygllib.cpp kanaset.cpp' )
src = {}
src['crossmingw'] = commonsrc + Split('windows.cpp')
src['gcc'] = commonsrc + Split('main.cpp')
ldflags = {}
ldflags['crossmingw'] = ['-Wl,--subsystem,windows']
ldflags['gcc'] = []
env . Program( 'darkhistory', src[tools], LIBS=lib[tools], LINKFLAGS=ldflags[tools])
