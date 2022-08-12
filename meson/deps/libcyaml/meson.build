libcyaml_srcs = [files(
  '../../../submodules/libcyaml/include/cyaml/cyaml.h',
  '../../../submodules/libcyaml/src/free.c',
  '../../../submodules/libcyaml/src/load.c',
  '../../../submodules/libcyaml/src/mem.c',
  '../../../submodules/libcyaml/src/mem.h',
  '../../../submodules/libcyaml/src/save.c',
  '../../../submodules/libcyaml/src/utf8.c',
  '../../../submodules/libcyaml/src/utf8.h',
  '../../../submodules/libcyaml/src/util.c',
  '../../../submodules/libcyaml/src/util.h',
)]

libcyaml_dirs = [
  '../../../submodules/libcyaml',
  '../../../submodules/libcyaml/include',
  '../../../submodules/libcyaml/include/cyaml',
  '../../../submodules/libcyaml/src',
  inc,
]

libcyaml_deps = [

]

libcyaml_lib = library('libcyaml',
  libcyaml_srcs,
  install: false,
  dependencies: libcyaml_deps,
  include_directories: libcyaml_dirs,
)

libcyaml_dep = declare_dependency(
  include_directories: libcyaml_dirs,
  link_with: libcyaml_lib,
)
