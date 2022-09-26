curses_speedtest_srcs = [files(

)]

curses_speedtest_dirs = [
  '../../../submodules/curses_speedtest',
  inc,
]

curses_speedtest_deps = [

]

curses_speedtest_lib =library('curses_speedtest',
  curses_speedtest_srcs,
  install: false,
  dependencies: curses_speedtest_deps,
  include_directories: curses_speedtest_dirs,
)

curses_speedtest_dep = declare_dependency(
  include_directories: curses_speedtest_dirs,
  link_with: curses_speedtest_lib,
)
