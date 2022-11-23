sqlite3_dep = cc.find_library('sqlite3', required: true)
sqlite_dep = sqlite3_dep

add_global_link_arguments('-lsqlite3',     language : ['c'])
add_global_arguments('-DSQLDBAL_SQLITE',language:['c'])
