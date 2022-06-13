tinydir_lib = library('tinydir',
  install: false, 
  dependencies: [
   timestamp_dep, 
  ], 
  include_directories: [
    inc,
  ]
)
tinydir_dep = declare_dependency(include_directories: [inc], link_with: tinydir_lib)
