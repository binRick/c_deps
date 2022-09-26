c_string_buffer_dir =  'submodules/c_string_buffer'
c_string_buffer_srcs = [
  c_deps_dir + '/' + c_string_buffer_dir + '/src/stringbuffer.c',
]
c_string_buffer_inc = [
  '../../../submodules/c_string_buffer',
  '../../../submodules/c_string_buffer/include',
  '../../../submodules/c_string_buffer/src',
  inc,
]
_c_string_buffer_inc = [
  c_string_buffer_dir,
  c_string_buffer_dir + '/include',
  c_string_buffer_dir + '/src',
]

c_string_buffer_lib =library('c_string_buffer', c_string_buffer_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: c_string_buffer_inc,
)

c_string_buffer_dep = declare_dependency(
  include_directories: c_string_buffer_inc,
  link_with: c_string_buffer_lib,
)

