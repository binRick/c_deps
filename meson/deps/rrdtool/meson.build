
rrdtool_srcs = [files(
  '../../../submodules/rrdtool/src/hash_32.c',
  '../../../submodules/rrdtool/src/mutex.c',
  '../../../submodules/rrdtool/src/pngsize.c',
  '../../../submodules/rrdtool/src/optparse.c',
  '../../../submodules/rrdtool/src/quicksort.c',
  '../../../submodules/rrdtool/src/rrd_client.c',
  '../../../submodules/rrdtool/src/rrd_create.c',
  '../../../submodules/rrdtool/src/rrd_daemon.c',
  '../../../submodules/rrdtool/src/rrd_datalang.c',
  '../../../submodules/rrdtool/src/rrd_diff.c',
  '../../../submodules/rrdtool/src/rrd_dump.c',
  '../../../submodules/rrdtool/src/rrd_error.c',
  '../../../submodules/rrdtool/src/rrd_fetch.c',
  '../../../submodules/rrdtool/src/rrd_fetch_cb.c',
  '../../../submodules/rrdtool/src/rrd_first.c',
  '../../../submodules/rrdtool/src/rrd_format.c',
  '../../../submodules/rrdtool/src/rrd_gfx.c',
  '../../../submodules/rrdtool/src/rrd_graph.c',
  '../../../submodules/rrdtool/src/rrd_graph_helper.c',
  '../../../submodules/rrdtool/src/rrd_hw.c',
  '../../../submodules/rrdtool/src/rrd_hw_math.c',
  '../../../submodules/rrdtool/src/rrd_hw_update.c',
  '../../../submodules/rrdtool/src/rrd_info.c',
  '../../../submodules/rrdtool/src/rrd_last.c',
  '../../../submodules/rrdtool/src/rrd_lastupdate.c',
  '../../../submodules/rrdtool/src/rrd_list.c',
  '../../../submodules/rrdtool/src/rrd_modify.c',
  '../../../submodules/rrdtool/src/rrd_nan_inf.c',
  '../../../submodules/rrdtool/src/rrd_open.c',
  '../../../submodules/rrdtool/src/rrd_parsetime.c',
  '../../../submodules/rrdtool/src/rrd_resize.c',
  '../../../submodules/rrdtool/src/rrd_restore.c',
  '../../../submodules/rrdtool/src/rrd_rpncalc.c',
  '../../../submodules/rrdtool/src/rrd_strtod.c',
  '../../../submodules/rrdtool/src/rrd_thread_safe.c',
  '../../../submodules/rrdtool/src/rrd_tune.c',
  '../../../submodules/rrdtool/src/rrd_update.c',
  '../../../submodules/rrdtool/src/rrd_utils.c',
  '../../../submodules/rrdtool/src/rrd_xport.c',
  '../../../submodules/rrdtool/src/rrdupdate.c',
  '../../../submodules/rrdtool/src/strftime.c',
)]

rrdtool_dirs = [
  '../../../submodules/rrdtool',
  '../../../submodules/rrdtool/src',
  inc,
]


rrdtool_c_args = [
  '-DLOCALSTATEDIR="/tmp"',
  ]

cairo_dep = dependency('cairo',required:true)
glib_dep = dependency('glib-2.0',required:true)
pango_dep = dependency('pango',required:true)
pcre_dep = dependency('libpcre',required:true)
png_dep = dependency('libpng',required:true)
xml2_dep = dependency('libxml-2.0',required:true)
harfbuzz_dep = dependency('harfbuzz',required:true)
pangocairo_dep = dependency('pangocairo',required:true)
gobject_dep = dependency('gobject-2.0',required:true)

rrdtool_deps = [
  gobject_dep, 
  pangocairo_dep,
  harfbuzz_dep,
  cairo_dep,
  pango_dep,
  glib_dep,
  pcre_dep,
  png_dep,
  xml2_dep,
]

rrdtool_lib = library('rrdtool',
  rrdtool_srcs,
  install: false,
  dependencies: rrdtool_deps,
  include_directories: rrdtool_dirs,
  c_args: rrdtool_c_args,
)

rrdtool_dep = declare_dependency(
  include_directories: rrdtool_dirs,
  link_with: rrdtool_lib,
)
