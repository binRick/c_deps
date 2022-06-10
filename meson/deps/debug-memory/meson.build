debug_memory_lib = library('debug-memory', 
  pwd + '/submodules/debug-memory/debug_memory.c',
  install: false, 
  dependencies: [], 
  include_directories: inc,
)
debug_memory_dep = declare_dependency(include_directories: inc,
  link_with: debug_memory_lib,
)
