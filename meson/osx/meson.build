osx_audit_flags = get_variable('osx_audit_flags', [])
osx_ldflags =     get_variable('osx_ldflags', [])
osx_wg_flags =     get_variable('osx_wgflags', [])


osx_ldflags +=  ['-Wl,-framework,CoreFoundation']
osx_ldflags +=  ['-Wl,-framework,Carbon']
osx_ldflags +=  ['-Wl,-framework,ApplicationServices']
osx_ldflags +=  ['-Wl,-framework,Foundation']
osx_ldflags +=  ['-Wl,-framework,AppKit']

osx_audit_flags +=  ['-lbsm']

osx_wg_flags +=  ['-MMD']
osx_wg_flags +=  ['-MP']
osx_wg_flags +=  ['-DRUNSTATEDIR=/var/run']

add_project_link_arguments(osx_ldflags,     language : ['c'])
add_project_link_arguments(osx_audit_flags, language : ['c'])
add_project_link_arguments(osx_wg_flags, language : ['c'])




#osx_ldflags += ['-Wl,-framework OpenGL']
#add_project_link_arguments(osx_ldflags, language : ['objc', 'c'])
