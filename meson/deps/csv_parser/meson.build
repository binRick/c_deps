csv_parser_system_headers = [

]
csv_parser_local_headers = [
  'csv_parser/csv.h',
]
csv_parser_srcs = [
  '../../../submodules/csv_parser/csv.c',
  '../../../submodules/csv_parser/fread_csv_line.c',
  '../../../submodules/csv_parser/split.c',
]

csv_parser_dirs = [
  '../../../submodules/csv_parser',
  inc,
]

csv_parser_c_args = [
]

csv_parser_deps = [

]

if csv_parser_srcs.length() > 0
  csv_parser_lib = library('csv_parser',
    files(csv_parser_srcs),
    install: false,
    dependencies: csv_parser_deps,
    include_directories: csv_parser_dirs,
    c_args: csv_parser_c_args,
  )
  csv_parser_links = [csv_parser_lib]
else
  csv_parser_links = []
endif

csv_parser_dep = declare_dependency(
  include_directories: csv_parser_dirs,
  link_with: csv_parser_links,
)
