c_eventemitter_inc = [
  '../../../submodules/c_eventemitter/include',
  '../../../submodules/c_eventemitter/src',
  '../../../submodules/c_eventemitter',
  inc,
]
c_eventemitter_lib =library('c_eventemitter', 
  '../../../submodules/c_eventemitter/src/eventemitter.c',
  install: false, 
  dependencies: [
    c_vector_dep,
  ], 
  include_directories: c_eventemitter_inc,
)
c_eventemitter_dep = declare_dependency(
  include_directories: c_eventemitter_inc,
  link_with: c_eventemitter_lib,
)
