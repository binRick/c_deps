debug_memory_inc = [
    inc,
  '../../../submodules/debug-memory',
]
debug_memory_lib = both_libraries('debug-memory', 
  '../../../submodules/debug-memory/debug_memory.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: inc,
)
debug_memory_dep = declare_dependency(include_directories: debug_memory_inc,
  link_with: debug_memory_lib,
)
