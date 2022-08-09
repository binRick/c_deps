chfreq_c_srcs = [files(
  '../../../submodules/chfreq.c/chfreq.c',
)]

chfreq_c_dirs = [
  '../../../submodules/chfreq.c',
  inc,
]

chfreq_c_deps = [

]

chfreq_c_lib = static_library('chfreq-c',
  chfreq_c_srcs,
  install: false,
  dependencies: chfreq_c_deps,
  include_directories: chfreq_c_dirs,
)

chfreq_c_dep = declare_dependency(
  include_directories: chfreq_c_dirs,
  link_with: chfreq_c_lib,
)
