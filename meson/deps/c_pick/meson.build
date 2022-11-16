c_pick_system_headers = [

]
c_pick_local_headers = [
  'c_pick/libpick/config.h',
  'c_pick/libpick/libpick.h',
  'c_pick/libpick/pty.h',
]
c_pick_srcs = [
  '../../../submodules/c_pick/libpick/libpick.c',
  '../../../submodules/c_pick/libpick/pty.c',
  '../../../submodules/c_pick/libpick/compat-reallocarray.c',
]

c_pick_dirs = [
  '../../../submodules/c_pick',
  '../../../submodules/c_pick/libpick',
  inc,
]

c_pick_c_args = [
]

c_pick_deps = [
  c_vector_dep,
  curses_dep,
  c_fsio_dep,
  c_stringfn_dep,

]

if c_pick_srcs.length() > 0
  c_pick_lib = library('c_pick',
    files(c_pick_srcs),
    install: false,
    dependencies: c_pick_deps,
    include_directories: c_pick_dirs,
    c_args: c_pick_c_args,
  )
  c_pick_links = [c_pick_lib]
else
  c_pick_links = []
endif

c_pick_dep = declare_dependency(
  include_directories: c_pick_dirs,
  link_with: c_pick_links,
)
