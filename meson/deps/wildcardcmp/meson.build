wildcardcmp_lib = static_library('wildcardcmp',
  meson_deps_dir + '/submodules/wildcardcmp/wildcardcmp.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
wildcardcmp_dep = declare_dependency(include_directories: [inc], link_with: wildcardcmp_lib)
