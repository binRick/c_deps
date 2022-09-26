#####################################################################################
asprintf_name = 'asprintf'
asprintf_dir = c_deps_dir + '/submodules/asprintf.c'
asprintf_srcs = [
   asprintf_dir + '/asprintf.c',
]
asprintf_cflags = []
asprintf_dirs = [
  '../../../submodules/asprintf.c',
  '../../../submodules',
  ]
#####################################################################################


#####################################################################################
asprintf_lib =library(asprintf_name,asprintf_srcs, c_args: asprintf_cflags,include_directories: asprintf_dirs, )
asprintf_dep = declare_dependency(link_with: asprintf_lib,include_directories: asprintf_dirs)
#####################################################################################
