wg_dynamic_srcs = [files(
  #'../../../submodules/wg-dynamic/common.c',
  '../../../submodules/wg-dynamic/common.h',
  #  '../../../submodules/wg-dynamic/dbg.h',
  #'../../../submodules/wg-dynamic/ipm.c',
  #'../../../submodules/wg-dynamic/ipm.h',
  #'../../../submodules/wg-dynamic/khash.h',
  #'../../../submodules/wg-dynamic/lease.c',
  #'../../../submodules/wg-dynamic/lease.h',
  #'../../../submodules/wg-dynamic/netlink.c',
  #'../../../submodules/wg-dynamic/netlink.h',
  #'../../../submodules/wg-dynamic/radix-trie.c',
  #'../../../submodules/wg-dynamic/radix-trie.h',
  #'../../../submodules/wg-dynamic/random.c',
  #'../../../submodules/wg-dynamic/random.h',
  #'../../../submodules/wg-dynamic/siphash.c',
  #'../../../submodules/wg-dynamic/siphash.h',
  #'../../../submodules/wg-dynamic/wg-dynamic-client.c',
  #'../../../submodules/wg-dynamic/wg-dynamic-server.c',
)]

wg_dynamic_dirs = [
  '../../../submodules/wg-dynamic',
  inc,
]

wg_dynamic_deps = [

]

wg_dynamic_lib = shared_library('wg-dynamic',
  wg_dynamic_srcs,
  install: false,
  dependencies: wg_dynamic_deps,
  include_directories: wg_dynamic_dirs,
)

wg_dynamic_dep = declare_dependency(
  include_directories: wg_dynamic_dirs,
  link_with: wg_dynamic_lib,
)
