libucl_srcs = [files(
  '../../../submodules/libucl/src/ucl_emitter.c',
  '../../../submodules/libucl/src/ucl_emitter_streamline.c',
  '../../../submodules/libucl/src/ucl_emitter_utils.c',
  '../../../submodules/libucl/src/ucl_hash.c',
  '../../../submodules/libucl/src/ucl_msgpack.c',
  '../../../submodules/libucl/src/ucl_parser.c',
  '../../../submodules/libucl/src/ucl_schema.c',
  '../../../submodules/libucl/src/ucl_sexp.c',
  '../../../submodules/libucl/src/ucl_util.c',
)]

libucl_dirs = [
  '../../../submodules/libucl',
  '../../../submodules/libucl/include',
  '../../../submodules/libucl/src',
  '../../../submodules/libucl/utils',
  '../../../submodules/libucl/uthash',
  inc,
]

libucl_deps = [

]

libucl_lib =library('libucl',
  libucl_srcs,
  install: false,
  dependencies: libucl_deps,
  include_directories: libucl_dirs,
)

libucl_dep = declare_dependency(
  include_directories: libucl_dirs,
  link_with: libucl_lib,
)
