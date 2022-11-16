c_hl_system_headers = [

]
c_hl_local_headers = [
  'c_hl/.attic/parson/parson.h',
  'c_hl/ansilove-test/ansilove-test.h',
  'c_hl/ansilove/ansilove.h',
  'c_hl/hl-test/.attic/db-test.h',
  'c_hl/hl-test/hl-test.h',
  'c_hl/hl/hl.h',
  'c_hl/png-test/png-test.h',
  'c_hl/png/png.h',
  'c_hl/vendor/ansicodes/ansicodes.h',
  'c_hl/vendor/ansicodes/ansicodes1.h',
  'c_hl/vendor/ansicodes/ansidb.h',
  'c_hl/vendor/ansicodes/rgbansi.h',
]
c_hl_srcs = [
  '../../../submodules/c_hl/ansilove/ansilove.c',
  '../../../submodules/c_hl/hl/hl.c',
  '../../../submodules/c_hl/png/png.c',
]

c_hl_dirs = [
  '../../../submodules/c_hl',
  '../../../submodules/c_hl/ansilove',
  '../../../submodules/c_hl/hl',
  '../../../submodules/c_hl/png',
  inc,
]

c_hl_c_args = [
]

c_hl_deps = [

]

if c_hl_srcs.length() > 0
  c_hl_lib = library('c_hl',
    files(c_hl_srcs),
    install: false,
    dependencies: c_hl_deps,
    include_directories: c_hl_dirs,
    c_args: c_hl_c_args,
  )
  c_hl_links = [c_hl_lib]
else
  c_hl_links = []
endif

c_hl_dep = declare_dependency(
  include_directories: c_hl_dirs,
  link_with: c_hl_links,
)
