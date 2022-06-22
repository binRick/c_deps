sqlite = [
  meson_deps_dir+'/vendor/sqlite/sqlite3.c',
]

sqlite_cflags = [
    '-Wno-pointer-to-int-cast',
    '-Wno-int-to-void-pointer-cast',
	'-DSQLITE_OMIT_LOAD_EXTENSION',
	'-DSQLITE_THREADSAFE=0',
	'-DSQLITE_DEFAULT_AUTOVACUUM=1',
	'-DSQLITE_TEMP_STORE=3',
]

sqlite_incs = [
  '../../../vendor/sqlite',
]

sqlite_lib = static_library('sqlite3',
                             sqlite,
                             c_args: sqlite_cflags + ['-DBOYDEMDB_INTERNAL'],
                             include_directories: sqlite_incs
)

sqlite_dep = declare_dependency(
  link_with: sqlite_lib,
  include_directories: sqlite_incs,
)
