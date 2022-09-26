msgpack_c_srcs = [files(
  '../../../submodules/msgpack_c/src/objectc.c',
  '../../../submodules/msgpack_c/src/unpack.c',
  '../../../submodules/msgpack_c/src/version.c',
  '../../../submodules/msgpack_c/src/vrefbuffer.c',
  '../../../submodules/msgpack_c/src/zone.c',
)]

msgpack_c_dirs = [
  '../../../submodules/msgpack_c',
  '../../../submodules/msgpack_c/ci',
  '../../../submodules/msgpack_c/include',
  '../../../submodules/msgpack_c/include/msgpack',
  '../../../submodules/msgpack_c/src',
  inc,
]

msgpack_c_deps = [

]

msgpack_c_lib =library('msgpack_c',
  msgpack_c_srcs,
  install: false,
  dependencies: msgpack_c_deps,
  include_directories: msgpack_c_dirs,
)

msgpack_c_dep = declare_dependency(
  include_directories: msgpack_c_dirs,
  link_with: msgpack_c_lib,
)
