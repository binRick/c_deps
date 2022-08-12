c_unja_srcs = [files(
  '../../../submodules/c_unja/src/unja_hashmap.c',
  '../../../submodules/c_unja/src/unja_hashmap.h',
  '../../../submodules/c_unja/src/unja_template.c',
  '../../../submodules/c_unja/src/unja_template.h',
  '../../../submodules/c_unja/src/unja_vector.c',
  '../../../submodules/c_unja/src/unja_vector.h',
  '../../../submodules/c_unja/vendor/mpc.h',
  '../../../submodules/c_unja/vendor/mpc.c',
)]

c_unja_dirs = [
  '../../../submodules/c_unja',
  '../../../submodules/c_unja/src',
  inc,
]

c_unja_deps = [

]

c_unja_lib = both_libraries('unja',
  c_unja_srcs,
  install: false,
  dependencies: c_unja_deps,
  include_directories: c_unja_dirs,
)

c_unja_dep = declare_dependency(
  include_directories: c_unja_dirs,
  link_with: c_unja_lib,
)
