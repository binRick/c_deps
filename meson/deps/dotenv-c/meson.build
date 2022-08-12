dotenv_c_srcs = [files(
  '../../../submodules/dotenv-c/src/dotenv.c',
)]

dotenv_c_dirs = [
  '../../../submodules/dotenv-c',
  '../../../submodules/dotenv-c/src',
  inc,
]

dotenv_c_deps = [

]

dotenv_c_lib = library('dotenv-c',
  dotenv_c_srcs,
  install: false,
  dependencies: dotenv_c_deps,
  include_directories: dotenv_c_dirs,
)

dotenv_c_dep = declare_dependency(
  include_directories: dotenv_c_dirs,
  link_with: dotenv_c_lib,
)
