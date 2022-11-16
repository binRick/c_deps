c_exception_system_headers = [

]
c_exception_local_headers = [
  'c_exception/lib/CException.h',
]
c_exception_srcs = [
  '../../../submodules/c_exception/lib/CException.c',
]

c_exception_dirs = [
  '../../../submodules/c_exception',
  '../../../submodules/c_exception/lib',
  inc,
]

c_exception_c_args = [
]

c_exception_deps = [

]

if c_exception_srcs.length() > 0
  c_exception_lib = library('c_exception',
    files(c_exception_srcs),
    install: false,
    dependencies: c_exception_deps,
    include_directories: c_exception_dirs,
    c_args: c_exception_c_args,
  )
  c_exception_links = [c_exception_lib]
else
  c_exception_links = []
endif

c_exception_dep = declare_dependency(
  include_directories: c_exception_dirs,
  link_with: c_exception_links,
)
