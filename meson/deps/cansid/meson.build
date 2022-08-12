cansid_srcs = [  
  c_deps_dir + '/submodules/cansid/cansid.c',
]

cansid_lib = both_libraries('cansid',
  cansid_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
cansid_dep = declare_dependency(include_directories: [inc], link_with: cansid_lib)
