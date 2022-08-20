iowow_srcs = [files(
  '../../../submodules/iowow/src/fs/iwexfile.c',
  '../../../submodules/iowow/src/fs/iwfile.c',
  '../../../submodules/iowow/src/fs/iwfs.c',
  '../../../submodules/iowow/src/fs/iwfsmfile.c',
  '../../../submodules/iowow/src/iowow.c',
  '../../../submodules/iowow/src/json/iwbinn.c',
  '../../../submodules/iowow/src/json/iwjser.c',
  '../../../submodules/iowow/src/json/iwjson.c',
  '../../../submodules/iowow/src/kv/dbg/iwkvdbg.c',
  '../../../submodules/iowow/src/kv/iwal.c',
  '../../../submodules/iowow/src/kv/iwkv.c',
  '../../../submodules/iowow/src/log/iwlog.c',
  '../../../submodules/iowow/src/platform/iwp.c',
  '../../../submodules/iowow/src/platform/unix/unix.c',
  '../../../submodules/iowow/src/platform/win32/mman/mman.c',
  '../../../submodules/iowow/src/platform/win32/win32.c',
  '../../../submodules/iowow/src/rdb/iwrdb.c',
  '../../../submodules/iowow/src/re/compile.c',
  '../../../submodules/iowow/src/re/iwre.c',
  '../../../submodules/iowow/src/re/parse.c',
  '../../../submodules/iowow/src/re/vm.c',
  '../../../submodules/iowow/src/utils/iwarr.c',
  '../../../submodules/iowow/src/utils/iwavl.c',
  '../../../submodules/iowow/src/utils/iwconv.c',
  '../../../submodules/iowow/src/utils/iwhmap.c',
  '../../../submodules/iowow/src/utils/iwini.c',
  '../../../submodules/iowow/src/utils/iwpool.c',
  '../../../submodules/iowow/src/utils/iwrb.c',
  '../../../submodules/iowow/src/utils/iwstw.c',
  '../../../submodules/iowow/src/utils/iwth.c',
  '../../../submodules/iowow/src/utils/iwtp.c',
  '../../../submodules/iowow/src/utils/iwutils.c',
  '../../../submodules/iowow/src/utils/iwuuid.c',
  '../../../submodules/iowow/src/utils/iwxstr.c',
  '../../../submodules/iowow/src/utils/mt19937ar.c',
  '../../../submodules/iowow/src/utils/murmur3.c',
  '../../../submodules/iowow/src/utils/utf8proc.c',
)]

iowow_dirs = [
  '../../../submodules/iowow',
  '../../../submodules/iowow/src',
  '../../../submodules/iowow/src/fs',
  '../../../submodules/iowow/src/json',
  '../../../submodules/iowow/src/kv',
  '../../../submodules/iowow/src/kv/dbg',
  '../../../submodules/iowow/src/log',
  '../../../submodules/iowow/src/platform',
  '../../../submodules/iowow/src/platform/unix',
  '../../../submodules/iowow/src/rdb',
  '../../../submodules/iowow/src/re',
  '../../../submodules/iowow/src/tmpl',
  '../../../submodules/iowow/src/utils',
  inc,
]

iowow_deps = [

]

iowow_lib = both_libraries('iowow',
  iowow_srcs,
  install: false,
  dependencies: iowow_deps,
  include_directories: iowow_dirs,
)

iowow_dep = declare_dependency(
  include_directories: iowow_dirs,
  link_with: iowow_lib,
)
