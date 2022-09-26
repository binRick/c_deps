yder_srcs = [files(
  '../../../submodules/yder/src/yder.c',
)]

yder_dirs = [
  '../../../submodules/yder',
  '../../../submodules/yder/doc',
  '../../../submodules/yder/include',
  '../../../submodules/yder/src',
  inc,
]

yder_c_args = [
  '-DY_DISABLE_JOURNALD',
  ]
yder_deps = [
  orcania_dep,
]

yder_lib =library('yder',
  yder_srcs,
  install: false,
  dependencies: yder_deps,
  c_args: yder_c_args,
  include_directories: yder_dirs,
)

yder_dep = declare_dependency(
  include_directories: yder_dirs,
  link_with: yder_lib,
)
