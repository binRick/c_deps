slug_lib = static_library('slug',
  pwd + '/submodules/slug.c/src/slug.c',
  pwd + '/submodules/slug.c/deps/case.c',
  pwd + '/submodules/slug.c/deps/trim.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
slug_dep = declare_dependency(include_directories: [inc], link_with: slug_lib)
