c_timer_lib = library('c_timer', 
  '../../../submodules/c_timer/src/c_timer.c',
  install: false, 
  dependencies: [
    ms_dep,
    timestamp_dep,
    ansi_codes_dep,
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
