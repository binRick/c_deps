catpath_inc = [
  '../../../submodules/catpath',
  inc,
]
catpath_lib = library('catpath', 
  '../../../submodules/catpath/catpath.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: catpath_inc,
)
catpath_dep = declare_dependency(
  include_directories: catpath_inc,
  link_with: catpath_lib,
)
