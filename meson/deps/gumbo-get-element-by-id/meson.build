gumbo_id_lib = both_libraries('gumbo-id',
  pwd + '/submodules/gumbo-get-element-by-id.c/src/get-element-by-id.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
gumbo_id_dep = declare_dependency(include_directories: [inc], link_with: gumbo_id_lib)
