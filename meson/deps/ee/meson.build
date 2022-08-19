ee_lib = static_library('ee',
  c_deps_dir+'/submodules/ee.c/src/ee.c',
  install: false, 
  dependencies: [
    list_dep
  ], 
  include_directories: [
    inc,
  ]
)
ee_dep = declare_dependency(include_directories: [inc], link_with: ee_lib)
