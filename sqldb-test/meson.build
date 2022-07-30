sqldb_test_srcs = [
  'sqldb-test.c',
  'sqldb-test.h',
]
sqldb_include_dirs = [
  inc,
  '.',
  '../',
  '../submodules',
]
sqldb_test_sqldb = [
  c_vector_dep,
  
  c_timestamp_dep,
  timestamp_dep,
  c_stringfn_dep,
  c_fsio_dep,
  c_string_buffer_dep,
  logh_dep,
  sqldbal_dep,
  sqlite3_dep,
  c_forever_dep,
  dbg_dep,
  c_eventemitter_dep,
  dmt_dep,
  ansi_utils_dep,
]
sqldb_c_args = [
]
sqldb_link_args = [
]
if get_option('enable-binaries')
  sqldb_test_exec = executable('sqldb-test',
     sqldb_test_srcs,
     dependencies: sqldb_test_sqldb,
     include_directories: sqldb_include_dirs,
     link_args: sqldb_link_args,
     c_args: sqldb_c_args,
     install: true,
  )
  if get_option('enable-binary-tests')
    test('sqldb-test', 
      passh_program, args: [sqldb_test_exec,'-v','-a'],
      timeout: 60,
      is_parallel: true,
      workdir: meson.current_source_dir(),
      )
  endif
endif
