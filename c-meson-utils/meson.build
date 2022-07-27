c_meson_utils_srcs = [
  'c-meson-utils.c',
  'c-meson-utils.h',
]
c_meson_utils_incs = [
  inc,
  '../',
]
c_meson_utils_deps = [
  c_vector_dep,
  djbhash_dep,
  c_unja_dep,
  c_fsio_dep,
  c_string_buffer_dep,
  c_stringfn_dep,
]


c_meson_utils_lib = library('c-meson-utils', 
  c_meson_utils_srcs,
  install: false, 
  dependencies: c_meson_utils_deps,
  include_directories: c_meson_utils_incs,
)


c_meson_utils_dep = declare_dependency(
  include_directories: c_meson_utils_incs,
  link_with: c_meson_utils_lib,
)
