rgba_lib = static_library('rgba', 
  '../../../submodules/rgba/src/rgba.c',
  install: false, dependencies: [], 
  include_directories: inc,
)
rgba_dep = declare_dependency(include_directories: inc, link_with: rgba_lib)
