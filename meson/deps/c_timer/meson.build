c_timer_lib = library('c_timer', 
  pwd + '/submodules/meson_deps/submodules/c_timer/src/c_timer.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    inc
  ]
)
c_timer_dep = declare_dependency(include_directories: 
  [
    inc
    ], 
  link_with: c_timer_lib,
)
