wireguard_tools_srcs = [
  '../../../submodules/wireguard-tools/contrib/embeddable-wg-library/wireguard.h',
  #//'../../../submodules/wireguard-tools/contrib/embeddable-wg-library/wireguard.c',
  #'../../../submodules/wireguard-tools/contrib/highlighter/highlight.c',
  #'../../../submodules/wireguard-tools/contrib/highlighter/highlighter.c',
  #'../../../submodules/wireguard-tools/contrib/highlighter/highlighter.h',
  #'../../../submodules/wireguard-tools/contrib/nat-hole-punching/nat-punch-client.c',
  #'../../../submodules/wireguard-tools/contrib/nat-hole-punching/nat-punch-server.c',
  #'../../../submodules/wireguard-tools/contrib/sticky-sockets/sticky-sockets.c',
  '../../../submodules/wireguard-tools/src/config.c',
  #'../../../submodules/wireguard-tools/src/ctype.h',
  '../../../submodules/wireguard-tools/src/curve25519-fiat32.h',
  '../../../submodules/wireguard-tools/src/curve25519-hacl64.h',
  '../../../submodules/wireguard-tools/src/curve25519.c',
  '../../../submodules/wireguard-tools/src/curve25519.h',
  '../../../submodules/wireguard-tools/src/encoding.c',
  '../../../submodules/wireguard-tools/src/encoding.h',
  '../../../submodules/wireguard-tools/src/genkey.c',
  '../../../submodules/wireguard-tools/src/ipc-freebsd.h',
  '../../../submodules/wireguard-tools/src/ipc-linux.h',
  '../../../submodules/wireguard-tools/src/ipc-openbsd.h',
  '../../../submodules/wireguard-tools/src/ipc-uapi-unix.h',
  '../../../submodules/wireguard-tools/src/ipc-uapi.h',
  '../../../submodules/wireguard-tools/src/ipc.c',
  '../../../submodules/wireguard-tools/src/ipc.h',
  '../../../submodules/wireguard-tools/src/netlink.h',
  '../../../submodules/wireguard-tools/src/pubkey.c',
  '../../../submodules/wireguard-tools/src/set.c',
  '../../../submodules/wireguard-tools/src/setconf.c',
  '../../../submodules/wireguard-tools/src/show.c',
  '../../../submodules/wireguard-tools/src/showconf.c',
  '../../../submodules/wireguard-tools/src/subcommands.h',
  '../../../submodules/wireguard-tools/src/terminal.c',
  '../../../submodules/wireguard-tools/src/terminal.h',
  '../../../submodules/wireguard-tools/src/uapi/freebsd/dev/if_wg/if_wg.h',
  '../../../submodules/wireguard-tools/src/uapi/linux/linux/wireguard.h',
  '../../../submodules/wireguard-tools/src/uapi/openbsd/net/if_wg.h',
  '../../../submodules/wireguard-tools/src/version.h',
  #'../../../submodules/wireguard-tools/src/wg-quick/android.c',
  '../../../submodules/wireguard-tools/src/wg.c',
]

wireguard_tools_dirs = [
  '../../../submodules/wireguard-tools',
  '../../../submodules/wireguard-tools/src',
  '../../../submodules/wireguard-tools/contrib',
  '../../../submodules/wireguard-tools/contrib/embeddable-wg-library',
  inc,
  #  '../../../submodules/wireguard-tools/contrib/dns-hatchet',
  #'../../../submodules/wireguard-tools/contrib/highlighter',
  #'../../../submodules/wireguard-tools/contrib/json',
  #'../../../submodules/wireguard-tools/contrib/keygen-html',
  #'../../../submodules/wireguard-tools/contrib/launchd',
  #'../../../submodules/wireguard-tools/contrib/nat-hole-punching',
  #'../../../submodules/wireguard-tools/contrib/ncat-client-server',
  #'../../../submodules/wireguard-tools/contrib/reresolve-dns',
  #'../../../submodules/wireguard-tools/contrib/sticky-sockets',
  #'../../../submodules/wireguard-tools/contrib/synergy',
  #'../../../submodules/wireguard-tools/src/completion',
  #'../../../submodules/wireguard-tools/src/systemd',
  #'../../../submodules/wireguard-tools/src/uapi',
  #'../../../submodules/wireguard-tools/src/uapi/freebsd/dev/if_wg',
  #'../../../submodules/wireguard-tools/src/uapi/linux/linux',
  #'../../../submodules/wireguard-tools/src/uapi/openbsd/net',
  #'../../../submodules/wireguard-tools/src/wg-quick',
]

wireguard_tools_deps = [

]
wireguard_c_args = [
  '-DRUNSTATEDIR="/var/run"',
]

wireguard_tools_lib = library('wireguard-tools',
  wireguard_tools_srcs,
  c_args: wireguard_c_args,
  install: false,
  dependencies: wireguard_tools_deps,
  include_directories: wireguard_tools_dirs,
)


wireguard_tools_dep = declare_dependency(
  include_directories: wireguard_tools_dirs,
  link_with: wireguard_tools_lib,
)
