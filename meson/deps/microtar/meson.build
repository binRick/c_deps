microtar_inc = [
  '../../../submodules/microtar/src',
  '../../../submodules/microtar',
  inc,
]
microtar_lib = library('microtar', 
  '../../../submodules/microtar/src/microtar.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: microtar_inc,
)
microtar_dep = declare_dependency(
  include_directories: microtar_inc,
  link_with: microtar_lib,
)
