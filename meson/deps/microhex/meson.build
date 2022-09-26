microhex_system_headers = [

]
microhex_local_headers = [
  'microhex/microhex.h',
]
microhex_srcs = [
  '../../../submodules/microhex/microhex.c',
]

microhex_dirs = [
  '../../../submodules/microhex',
  inc,
]

microhex_c_args = [
]

microhex_deps = [

]

if microhex_srcs.length() > 0
  microhex_lib =library('microhex',
    files(microhex_srcs),
    install: false,
    dependencies: microhex_deps,
    include_directories: microhex_dirs,
    c_args: microhex_c_args,
  )
  microhex_links = [microhex_lib]
else
  microhex_links = []
endif

microhex_dep = declare_dependency(
  include_directories: microhex_dirs,
  link_with: microhex_links,
)
