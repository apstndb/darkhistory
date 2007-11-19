#tools = ARGUMENTS.get( 'tools', 'gcc' )
#Tool( 'crossmingw' )(env)
#Tool( 'g++' )(env)
#Export('env')
#Export('tools')
tools = 'gcc'
SConscript( 'SConscript', exports=['tools'], build_dir='build-'+tools, duplicate=0 )
tools = 'crossmingw'
SConscript( 'SConscript', exports=['tools'], build_dir='build-'+tools, duplicate=0 )
