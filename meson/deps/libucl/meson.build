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
  '../../../submodules/libucl/utils/chargen.c',
  '../../../submodules/libucl/utils/objdump.c',
  '../../../submodules/libucl/utils/ucl-tool.c',
)]

libucl_dirs = [
  '../../../submodules/libucl',
  '../../../submodules/libucl/doc',
  '../../../submodules/libucl/haskell',
  '../../../submodules/libucl/include',
  '../../../submodules/libucl/klib',
  '../../../submodules/libucl/lua',
  '../../../submodules/libucl/python',
  '../../../submodules/libucl/python/src',
  '../../../submodules/libucl/src',
  '../../../submodules/libucl/uthash',
  inc,
]

libucl_deps = [

]

libucl_lib = static_library('libucl',
  libucl_srcs,
  install: false,
  dependencies: libucl_deps,
  include_directories: libucl_dirs,
)

libucl_dep = declare_dependency(
  include_directories: libucl_dirs,
  link_with: libucl_lib,
)
