c_string_buffer_dir =  'submodules/c_string_buffer'
c_string_buffer_srcs = [
  meson_deps_dir + '/' + c_string_buffer_dir + '/src/stringbuffer.c',
]
c_string_buffer_inc = [
  inc,
]
_c_string_buffer_inc = [
  c_string_buffer_dir,
  c_string_buffer_dir + '/include',
  c_string_buffer_dir + '/src',
]

c_string_buffer_lib = static_library('c_string_buffer', c_string_buffer_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: c_string_buffer_inc,
)

c_string_buffer_dep = declare_dependency(
  include_directories: c_string_buffer_inc,
  link_with: c_string_buffer_lib,
)

