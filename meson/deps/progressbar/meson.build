progressbar_lib = static_library('progressbar',
  pwd + '/submodules/progressbar/lib/progressbar.c',
  pwd + '/submodules/progressbar/lib/statusbar.c',
  install: false, 
  dependencies: [
    curses_dep,
  ], 
  include_directories: [
    inc,
  ]
)
progressbar_dep = declare_dependency(include_directories: [inc], link_with: progressbar_lib)
