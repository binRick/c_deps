progressbar_srcs = [
  meson_deps_dir + '/submodules/progressbar/lib/progressbar.c',
  meson_deps_dir + '/submodules/progressbar/lib/statusbar.c',
]
progressbar_lib = static_library('progressbar',
  progressbar_srcs,
  install: false, 
  dependencies: [
    curses_dep,
  ], 
  include_directories: [
    inc,
  ]
)
progressbar_dep = declare_dependency(include_directories: [inc], link_with: progressbar_lib)
