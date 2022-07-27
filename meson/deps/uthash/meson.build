uthash_srcs = [files(
  '../../../submodules/uthash/src/utarray.h',
  '../../../submodules/uthash/src/uthash.h',
  '../../../submodules/uthash/src/utlist.h',
  '../../../submodules/uthash/src/utringbuffer.h',
  '../../../submodules/uthash/src/utstack.h',
  '../../../submodules/uthash/src/utstring.h',
)]

uthash_dirs = [
  '../../../submodules/uthash',
  '../../../submodules/uthash/doc',
  '../../../submodules/uthash/src',
  inc,
]

uthash_deps = [

]

uthash_lib = shared_library('uthash',
  uthash_srcs,
  install: false,
  dependencies: uthash_deps,
  include_directories: uthash_dirs,
)

uthash_dep = declare_dependency(
  include_directories: uthash_dirs,
  link_with: uthash_lib,
)
