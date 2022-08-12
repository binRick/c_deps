which_srcs = [
  c_deps_dir + '/submodules/which/src/which.c',
]  
which_lib = both_libraries('which',
  which_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
which_dep = declare_dependency(include_directories: [inc], link_with: which_lib)
