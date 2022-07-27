unja_srcs = [files(
  '../../../submodules/unja/src/hashmap.c',
  '../../../submodules/unja/src/hashmap.h',
  '../../../submodules/unja/src/template.c',
  '../../../submodules/unja/src/template.h',
  '../../../submodules/unja/src/vector.c',
  '../../../submodules/unja/src/vector.h',
  '../../../submodules/unja/vendor/mpc.h',
  '../../../submodules/unja/vendor/mpc.c',
)]

unja_dirs = [
  '../../../submodules/unja',
  '../../../submodules/unja/src',
  inc,
]

unja_deps = [

]

unja_lib = shared_library('unja',
  unja_srcs,
  install: false,
  dependencies: unja_deps,
  include_directories: unja_dirs,
)

unja_dep = declare_dependency(
  include_directories: unja_dirs,
  link_with: unja_lib,
)
