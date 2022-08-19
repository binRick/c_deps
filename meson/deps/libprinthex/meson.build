libprinthex_srcs = [files(
  '../../../submodules/libprinthex/printhex.c',
)]

libprinthex_dirs = [
  '../../../submodules/libprinthex',
  inc,
]

libprinthex_deps = [

]

libprinthex_lib = both_libraries('libprinthex',
  libprinthex_srcs,
  install: false,
  dependencies: libprinthex_deps,
  include_directories: libprinthex_dirs,
)

libprinthex_dep = declare_dependency(
  include_directories: libprinthex_dirs,
  link_with: libprinthex_lib,
)
