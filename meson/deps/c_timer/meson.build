c_timer_lib = static_library('c_timer', 
  meson_deps_dir + '/submodules/c_timer/src/c_timer.c',
  install: false, 
  dependencies: [
    ms_dep,
    timestamp_dep,
    asprintf_dep,
  ], 
  include_directories: [
    inc
  ]
)
c_timer_dep = declare_dependency(
  include_directories: [
    inc
  ], 
  link_with: c_timer_lib,
)
