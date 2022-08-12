sense_c_srcs = [files(
  '../../../submodules/sense-c/src/git.c',
  '../../../submodules/sense-c/src/git.h',
  '../../../submodules/sense-c/src/lang.c',
  '../../../submodules/sense-c/src/lang.h',
)]

sense_c_dirs = [
  '../../../submodules/sense-c',
  '../../../submodules/sense-c/src',
  inc,
]

sense_c_deps = [

]

sense_c_lib = both_libraries('sense-c',
  sense_c_srcs,
  install: false,
  dependencies: sense_c_deps,
  include_directories: sense_c_dirs,
)

sense_c_dep = declare_dependency(
  include_directories: sense_c_dirs,
  link_with: sense_c_lib,
)
