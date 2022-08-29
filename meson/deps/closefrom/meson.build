closefrom_srcs = [files(
  '../../../submodules/main_renamer/pre.h',
  '../../../submodules/closefrom/closefrom.c',
  '../../../submodules/main_renamer/post.h',
)]

closefrom_dirs = [
  '../../../submodules/closefrom',
  inc,
]

closefrom_deps = [

]

closefrom_lib = static_library('closefrom',
  closefrom_srcs,
  install: false,
  dependencies: closefrom_deps,
  c_args: [
    '-DMAIN_RENAMER_NAME="closefrom"',
    ],
  include_directories: closefrom_dirs,
)

closefrom_dep = declare_dependency(
  include_directories: closefrom_dirs,
  link_with: closefrom_lib,
)
