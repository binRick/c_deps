readkey_srcs = [files(
  '../../../submodules/readkey/minilib.h',
  '../../../submodules/readkey/readkey.c',
)]

readkey_dirs = [
  '../../../submodules/readkey',
  inc,
]

readkey_deps = [

]

readkey_lib = static_library('readkey',
  readkey_srcs,
  install: false,
  dependencies: readkey_deps,
  include_directories: readkey_dirs,
)

readkey_dep = declare_dependency(
  include_directories: readkey_dirs,
  link_with: readkey_lib,
)
