libut_srcs = [files(
  '../../../submodules/libut/include/libut.h',
  '../../../submodules/libut/include/ringbuf.h',
  '../../../submodules/libut/include/utmm.h',
  '../../../submodules/libut/include/utvector.h',
  '../../../submodules/libut/src/libut.c',
  '../../../submodules/libut/src/ringbuf.c',
  '../../../submodules/libut/src/utmm.c',
  '../../../submodules/libut/src/utvector.c',
)]

libut_dirs = [
  '../../../submodules/libut',
  '../../../submodules/uthash',
  '../../../submodules/libut/include',
  '../../../submodules/libut/src',
  '../../../submodules/uthash/include',
  '../../../submodules/uthash/src',
  '../../../submodules/libut/uthash',
  inc,
]

libut_deps = [

]

libut_lib = shared_library('libut',
  libut_srcs,
  install: false,
  dependencies: libut_deps,
  include_directories: libut_dirs,
)

libut_dep = declare_dependency(
  include_directories: libut_dirs,
  link_with: libut_lib,
)
