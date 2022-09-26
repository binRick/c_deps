c_forever_inc = [
  '../../../submodules/c_forever/include',
  '../../../submodules/c_forever/src',
  '../../../submodules/c_forever',
  inc,
]
c_forever_lib =library('c_forever', 
  '../../../submodules/c_forever/src/forever.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: c_forever_inc,
)
c_forever_dep = declare_dependency(
  include_directories: c_forever_inc,
  link_with: c_forever_lib,
)
