c_timer_c_args = [
  '-Wno-unused-parameter',
  ]
c_timer_lib =library('c_timer', 
  c_deps_dir + '/submodules/c_timer/src/c_timer.c',
  install: false, 
  dependencies: [
    ms_dep,
    timestamp_dep,
    asprintf_dep,
  ], 
  include_directories: [
    inc
  ],
  c_args: c_timer_c_args,
)
c_timer_dep = declare_dependency(
  include_directories: [
    inc
  ], 
  link_with: c_timer_lib,
)
