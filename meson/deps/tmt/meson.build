tmt_lib = library('tmt',
  '../../../submodules/libtmt/tmt.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
  '../../../submodules/libtmt',
    inc,
  ]
)
tmt_dep = declare_dependency(include_directories: [inc], link_with: tmt_lib)
