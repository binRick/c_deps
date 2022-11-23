libcyaml_system_headers = [

]
libcyaml_local_headers = [
  'libcyaml/src/data.h',
  'libcyaml/src/mem.h',
  'libcyaml/src/utf8.h',
  'libcyaml/src/util.h',
]
libcyaml_srcs = [
  '../../../submodules/libcyaml/src/free.c',
  '../../../submodules/libcyaml/src/load.c',
  '../../../submodules/libcyaml/src/mem.c',
  '../../../submodules/libcyaml/src/save.c',
  '../../../submodules/libcyaml/src/utf8.c',
  '../../../submodules/libcyaml/src/util.c',
]

libcyaml_dirs = [
  '../../../submodules/libcyaml',
  '../../../submodules/libcyaml/include',
  '../../../submodules/libcyaml/include/cyaml',
  '../../../submodules/libcyaml/src',
  inc,
]

libcyaml_c_args = [
  '-DVERSION_MAJOR=1',
  '-DVERSION_MINOR=3',
  '-DVERSION_PATCH=1',
  '-DVERSION_DEVEL=1',
  '-MP',
  '-std=c11',
  '-Wall',
  '-Wextra',
  '-pedantic',
  '-Wconversion',
  '-Wwrite-strings',
  '-Wcast-align',
  '-Wpointer-arith',
  '-Winit-self',
  '-Wshadow',
  '-Wstrict-prototypes',
  '-Wmissing-prototypes',
  '-Wredundant-decls',
  '-Wundef',
  '-Wvla',
  '-Wdeclaration-after-statement',
  '-O0',
]
libcyaml_link_whole = [
  ]
libcyaml_deps = [
  yaml_dep,
]
libcyaml_static_lib = static_library('libcyaml',
    files(libcyaml_srcs),
    install: false,
    link_whole: libcyaml_link_whole,
    dependencies: libcyaml_deps,
    include_directories: libcyaml_dirs,
    c_args: libcyaml_c_args,
  )

if libcyaml_srcs.length() > 0
  libcyaml_lib = shared_library('libcyaml',
    files(libcyaml_srcs),
    install: false,
    dependencies: libcyaml_deps,
    include_directories: libcyaml_dirs,
    c_args: libcyaml_c_args,
  )
  libcyaml_links = [libcyaml_lib]
else
  libcyaml_links = []
endif

libcyaml_dep = declare_dependency(
  include_directories: libcyaml_dirs,
  link_with: libcyaml_links,
)
