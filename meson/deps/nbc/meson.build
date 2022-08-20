nbc_srcs = [files(
  '../../../submodules/nbc/src/core/__core.h',
  '../../../submodules/nbc/src/core/core.c',
  '../../../submodules/nbc/src/core/core.h',
  '../../../submodules/nbc/src/inte/__inte.h',
  '../../../submodules/nbc/src/inte/inte.c',
  '../../../submodules/nbc/src/inte/inte.h',
)]

nbc_dirs = [
  '../../../submodules/nbc',
  '../../../submodules/nbc/src',
  '../../../submodules/nbc/src/core',
  '../../../submodules/nbc/src/inte',
  inc,
]

nbc_deps = [

]

nbc_lib = both_libraries('nbc',
  nbc_srcs,
  install: false,
  dependencies: nbc_deps,
  include_directories: nbc_dirs,
)

nbc_dep = declare_dependency(
  include_directories: nbc_dirs,
  link_with: nbc_lib,
)
