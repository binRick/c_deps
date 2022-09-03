jansson_srcs = [files(
  '../../../submodules/jansson/src/dump.c',
  '../../../submodules/jansson/src/error.c',
  '../../../submodules/jansson/src/hashtable.c',
  '../../../submodules/jansson/src/hashtable_seed.c',
  '../../../submodules/jansson/src/load.c',
  '../../../submodules/jansson/src/memory.c',
  '../../../submodules/jansson/src/pack_unpack.c',
  '../../../submodules/jansson/src/strbuffer.c',
  '../../../submodules/jansson/src/strconv.c',
  '../../../submodules/jansson/src/value.c',
  '../../../submodules/jansson/src/utf.c',
  '../../../submodules/jansson/src/version.c',
)]

jansson_dirs = [
  '../../../submodules/jansson',
  '../../../submodules/jansson/src',
  '../../../submodules/jansson/include',
  '../../../submodules/jansson/private_include',
  inc,
]

jansson_c_args = [
  '-DHAVE_STDINT_H',

]
jansson_deps = [

]

jansson_lib = static_library('jansson',
  jansson_srcs,
  install: false,
  dependencies: jansson_deps,
  c_args: jansson_c_args,
  include_directories: jansson_dirs,
)

jansson_dep = declare_dependency(
  include_directories: jansson_dirs,
  link_with: jansson_lib,
)
