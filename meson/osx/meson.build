osx_ldflags = get_variable('osx_ldflags', [])
osx_ldflags +=  ['-Wl,-framework,CoreFoundation']
osx_ldflags += ['-Wl,-framework,Carbon']
osx_ldflags += ['-Wl,-framework,Foundation', '-Wl,-framework,AppKit']
add_project_link_arguments(osx_ldflags, language : ['c'])
#osx_ldflags += ['-Wl,-framework OpenGL']
#add_project_link_arguments(osx_ldflags, language : ['objc', 'c'])
