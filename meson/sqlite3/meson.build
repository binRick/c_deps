sqldbal_link_args = [
  '-lsqlite3',
]
sqldbal_c_args = [
  '-DSQLDBAL_SQLITE',
]
sqlite3_dep = dependency('sqlite3_dep',fallback:['sqlite3', 'sqlite3_dep'])
sqlite_dep = sqlite3_dep
add_project_arguments(sqldbal_c_args, language : 'c')
#add_project_link_arguments(sqldbal_link_args,language : ['c'])
