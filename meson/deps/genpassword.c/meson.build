genpassword_c_srcs = [files(
  '../../../submodules/genpassword.c/src/genpassword.c',
  '../../../submodules/genpassword.c/src/genpassword.h',
)]

genpassword_c_dirs = [
  '../../../submodules/genpassword.c',
  '../../../submodules/genpassword.c/src',
  inc,
]

genpassword_c_deps = [

]

genpassword_c_lib =library('genpassword.c',
  genpassword_c_srcs,
  install: false,
  dependencies: genpassword_c_deps,
  include_directories: genpassword_c_dirs,
)

genpassword_c_dep = declare_dependency(
  include_directories: genpassword_c_dirs,
  link_with: genpassword_c_lib,
)
