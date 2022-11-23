which_srcs = [
  c_deps_dir + '/submodules/which/src/which.c',
]  
which_lib_static =static_library('which',
  which_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
which_lib =shared_library('which',
  which_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
which_dep = declare_dependency(include_directories: [inc], link_with: which_lib)
