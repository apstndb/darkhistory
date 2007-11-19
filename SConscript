#Import( 'expenv' )
env = Environment( CPPPATH="/usr/include/freetype2" )
Import( 'tools' )
#env = expenv
Tool( tools )(env)
commonlibs = Split( 'glfw ftgl' )
lib = {}
lib['crossmingw'] = commonlibs + Split( 'opengl32 glu32')
lib['gcc'] = commonlibs + Split( 'GLU' )
src = Split( 'darkhistory.cpp game.cpp mylib.cpp mygllib.cpp kanaset.cpp' )
env . Program( 'darkhistory', src, LIBS=lib[tools] )
env . File( 'roma2hira.dat' )
