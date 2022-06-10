strdup_lib = library('strdup', 
pwd + '/submodules/strdup/strdup.c',
install: false, dependencies: [
  ], 
  include_directories: inc,
)
strdup_dep = declare_dependency(include_directories: inc,
link_with: strdup_lib)
