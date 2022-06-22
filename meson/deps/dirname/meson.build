dirname_inc = [
  '../../../submodules/dirname',
  inc,
]
dirname_lib = library('dirname', 
  '../../../submodules/dirname/dirname.h',
  install: false, 
  dependencies: [
  ], 
  include_directories: dirname_inc,
)
dirname_dep = declare_dependency(
  include_directories: dirname_inc,
  link_with: dirname_lib,
)
