cbars_system_headers = [

]
cbars_local_headers = [
  'cbars/include/cbars/cbars.h',
]
cbars_srcs = [
  '../../../submodules/cbars/src/cbars.c',
]

cbars_dirs = [
  '../../../submodules/cbars',
  '../../../submodules/cbars/include',
  '../../../submodules/cbars/include/cbars',
  '../../../submodules/cbars/src',
  inc,
]

cbars_c_args = [
]

cbars_deps = [

]

if cbars_srcs.length() > 0
  cbars_lib = library('cbars',
    files(cbars_srcs),
    install: false,
    dependencies: cbars_deps,
    include_directories: cbars_dirs,
    c_args: cbars_c_args,
  )
  cbars_links = [cbars_lib]
else
  cbars_links = []
endif

cbars_dep = declare_dependency(
  include_directories: cbars_dirs,
  link_with: cbars_links,
)
