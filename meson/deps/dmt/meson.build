dmt_inc = [
  '../../../submodules/dmt/src',
  '../../../submodules/dmt',
  inc,
]
dmt_lib = library('dmt', 
  '../../../submodules/dmt/src/dmt.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: dmt_inc,
)
dmt_dep = declare_dependency(
  include_directories: dmt_inc,
  link_with: dmt_lib,
)
