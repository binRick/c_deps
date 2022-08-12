progressbar_srcs = [
  c_deps_dir + '/submodules/progressbar/lib/progressbar.c',
  c_deps_dir + '/submodules/progressbar/lib/statusbar.c',
]

progressbar_lib = both_libraries('progressbar',
  progressbar_srcs,
  install: false, 
  dependencies: [
    curses_dep,
  ], 
  include_directories: [
  '../../../submodules/progressbar/lib',
  '../../../submodules/progressbar/include',
    inc,
  ]
)
progressbar_dep = declare_dependency(include_directories: [
  inc,
  '../../../submodules/progressbar/lib',
  ], link_with: progressbar_lib)
