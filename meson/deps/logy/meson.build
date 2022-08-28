logy_srcs = [files(
  '../../../submodules/logy/source/logger.c',
  '../../../submodules/logy/libraries/mpio/source/directory.c',
  '../../../submodules/logy/libraries/mpio/source/directory1.c',
  '../../../submodules/logy/libraries/mpmt/source/sync.c',
  '../../../submodules/logy/libraries/mpmt/source/thread.c',
  '../../../submodules/logy/libraries/mpmt/source/thread_pool.c',
)]

logy_dirs = [
  '../../../submodules/logy/libraries/mpmt/include',
  '../../../submodules/logy/libraries/mpmt',
  '../../../submodules/logy/libraries/mpio/include',
  '../../../submodules/logy/libraries/mpio',
  '../../../submodules/logy/libraries',
  '../../../submodules/logy/build/include',
  '../../../submodules/logy/include/logy',
  '../../../submodules/logy/include',
  '../../../submodules/logy/source',
  '../../../submodules/logy/build',
  '../../../submodules/logy',
  inc,
]

logy_deps = [

]

logy_lib = static_library('logy',
  logy_srcs,
  install: false,
  dependencies: logy_deps,
  include_directories: logy_dirs,
)

logy_dep = declare_dependency(
  include_directories: logy_dirs,
  link_with: logy_lib,
)
