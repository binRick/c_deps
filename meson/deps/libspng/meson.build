libspng_lib = static_library('libspng',
  pwd + '/submodules/libspng/spng/spng.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
libspng_dep = declare_dependency(include_directories: [inc], link_with: libspng_lib)
