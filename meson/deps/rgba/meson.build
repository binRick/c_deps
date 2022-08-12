rgba_dirs = [
  '../../../submodules/rgba/src',
  '../../../submodules/rgba',
  inc,
]
rgba_lib = library('rgba', 
  '../../../submodules/rgba/src/rgba.c',
  install: false, dependencies: [], 
  include_directories: rgba_dirs,
)
rgba_dep = declare_dependency(include_directories: rgba_dirs, link_with: rgba_lib)
