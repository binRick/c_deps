hs_srcs = [
  'hs.c',
]
hs_inc = [
 '../hs',
 '.',
 inc,
]
hs_deps = [
 greatest_dep,
 wireguard_tools_dep,
]


hs_lib = static_library('hs',
  hs_srcs,
  install: false,
  dependencies: hs_deps,
  include_directories: [
    hs_inc,
  ],
)

hs_dep = declare_dependency(
  include_directories: hs_inc,
  link_with: hs_lib,
)
