wg_srcs = [
  'wg.c',
]
wg_inc = [
 '../wg',
 '.',
 inc,
]
wg_deps = [
 c_greatest_dep,
 wireguard_tools_dep,
]


wg_lib = library('wg',
  wg_srcs,
  install: false,
  dependencies: wg_deps,
  include_directories: [
    wg_inc,
  ],
)

wg_dep = declare_dependency(
  include_directories: wg_inc,
  link_with: wg_lib,
)
