which_lib = static_library('which',
  pwd + '/submodules/which/src/which.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
which_dep = declare_dependency(include_directories: [inc], link_with: which_lib)
