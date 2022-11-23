c_bat_system_headers = [

]
c_bat_local_headers = [
  'c_bat/bat-test/bat-test.h',
  'c_bat/bat/bat.h',
]
c_bat_srcs = [
  '../../../submodules/c_bat/bat/bat.c',
]

c_bat_dirs = [
  '../../../submodules/c_bat',
  '../../../submodules/c_bat/bat',
  inc,
]

c_bat_c_args = [
]

c_bat_deps = [

  c_vector_dep,reproc_dep,which_dep,tempdir_dep,c_string_buffer_dep,
  c_fsio_dep,
  c_stringfn_dep,timestamp_dep,

]

if c_bat_srcs.length() > 0
  c_bat_lib = library('c_bat',
    files(c_bat_srcs),
    install: false,
    dependencies: c_bat_deps,
    include_directories: c_bat_dirs,
    c_args: c_bat_c_args,
  )
  c_bat_links = [c_bat_lib]
else
  c_bat_links = []
endif

c_bat_dep = declare_dependency(
  include_directories: c_bat_dirs,
  link_with: c_bat_links,
)
