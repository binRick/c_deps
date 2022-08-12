smaz_srcs = [
  c_deps_dir + '/submodules/smaz/smaz.c',
]  
smaz_lib = both_libraries('smaz', 
  smaz_srcs,
  install: false, 
  dependencies: [], 
  include_directories: [
    inc,
  ]
)
smaz_dep = declare_dependency(
  include_directories: [
    inc,
  ], 
  link_with: smaz_lib,
)
