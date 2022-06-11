strdup_lib = static_library('strdup', 
meson_deps_dir + '/submodules/strdup/strdup.c',
install: false, dependencies: [
  ], 
  include_directories: inc,
)
strdup_dep = declare_dependency(include_directories: inc,
link_with: strdup_lib)
