lzma_dep = dependency('liblzma', method: 'pkg-config', required: true)
zlib_dep = dependency('zlib', method: 'pkg-config', required: true)
libzstd_dep = dependency('libzstd', method: 'pkg-config', required: true)
lzo2_dep = dependency('lzo2', method: 'pkg-config', required: true)
liblz4_dep = dependency('liblz4', method: 'pkg-config', required: true)
libdeflate_dep = dependency('libdeflate', method: 'pkg-config', required: true)


termrec_system_headers = [
]
termrec_local_headers = [
  'termrec/common/common.h',
  'termrec/common/rec_args.h',
  'termrec/config.h',
  'termrec/export.h',
  'termrec/gettext.h',
  'termrec/libstream/compress.h',
  'termrec/libstream/stream.h',
  'termrec/libtty/charsets.h',
  'termrec/libtty/formats.h',
  'termrec/libtty/tty.h',
  'termrec/libtty/ttyrec.h',
  'termrec/libtty/wcwidth.h',
  'termrec/play/player.h',
  'termrec/rec/pty.h',
  'termrec/sys/compat.h',
  'termrec/sys/error.h',
  'termrec/sys/threads.h',
  'termrec/sys/ttysize.h',
  'termrec/sys/unix/threads.h',
  'termrec/sys/utils.h',
]
termrec_srcs = [
  '../../../submodules/termrec/common/args.c',
  '../../../submodules/termrec/common/open_out.c',
  '../../../submodules/termrec/common/rec_args.c',
  '../../../submodules/termrec/libstream/compress.c',
  '../../../submodules/termrec/libstream/prefix.c',
  '../../../submodules/termrec/libstream/stream.c',
  '../../../submodules/termrec/libstream/url_curl.c',
  '../../../submodules/termrec/libstream/url_file.c',
  '../../../submodules/termrec/libstream/url_tcp.c',
  '../../../submodules/termrec/libstream/url_telnet.c',
  '../../../submodules/termrec/libstream/url_termcast.c',
  '../../../submodules/termrec/libtty/asciicast.c',
  '../../../submodules/termrec/libtty/charsets.c',
  '../../../submodules/termrec/libtty/colors.c',
  '../../../submodules/termrec/libtty/dosrecorder.c',
  '../../../submodules/termrec/libtty/files.c',
  '../../../submodules/termrec/libtty/formats.c',
  '../../../submodules/termrec/libtty/timeline.c',
  '../../../submodules/termrec/libtty/tty.c',
  '../../../submodules/termrec/libtty/vtredir.c',
  '../../../submodules/termrec/libtty/wcwidth.c',
  '../../../submodules/termrec/sys/asprintf.c',
  '../../../submodules/termrec/sys/debuglog.c',
  '../../../submodules/termrec/sys/unix/ttysize.c',
  '../../../submodules/termrec/sys/unix/utils.c',
]

termrec_dirs = [
  '../../../submodules/termrec',
  '../../../submodules/termrec/cat',
  '../../../submodules/termrec/common',
  '../../../submodules/termrec/doc',
  '../../../submodules/termrec/libstream',
  '../../../submodules/termrec/libtty',
  '../../../submodules/termrec/play',
  '../../../submodules/termrec/rec',
  '../../../submodules/termrec/sys',
  '../../../submodules/termrec/sys/unix',
  '../../../submodules/termrec/time',
  inc,
]

termrec_c_args = [
]

termrec_deps = [
lzma_dep,
curl_dep,
libzstd_dep,
liblz4_dep,
libdeflate_dep,
zlib_dep,
lzo2_dep,
]

if termrec_srcs.length() > 0
  termrec_lib = static_library('termrec',
    files(termrec_srcs),
    install: false,
    dependencies: termrec_deps,
    include_directories: termrec_dirs,
    c_args: termrec_c_args,
  )
  termrec_links = [termrec_lib]
else
  termrec_links = []
endif

termrec_dep = declare_dependency(
  include_directories: termrec_dirs,
  link_with: termrec_links,
)
