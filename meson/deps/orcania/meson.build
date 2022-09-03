orcania_srcs = [files(
  '../../../submodules/orcania/src/base64.c',
  '../../../submodules/orcania/src/memory.c',
  '../../../submodules/orcania/src/orcania.c',
)]

orcania_dirs = [
  '../../../submodules/orcania',
  '../../../submodules/orcania/doc',
  '../../../submodules/orcania/include',
  '../../../submodules/orcania/src',
  inc,
]

orcania_deps = [
]

orcania_lib = static_library('orcania',
  orcania_srcs,
  install: false,
  dependencies: orcania_deps,
  include_directories: orcania_dirs,
)

orcania_dep = declare_dependency(
  include_directories: orcania_dirs,
  link_with: orcania_lib,
)
