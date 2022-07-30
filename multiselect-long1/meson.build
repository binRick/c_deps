go_name = 'multiselect-long1'
go_files = [
  go_name + '.go',
]
multiselect_long1_srcs = [
  go_name + '.c',
  go_name + '.h',
]
multiselect_long1_objects = [
  go_name + '.a',
]
multiselect_long1_dirs = [
  '.',
]
multiselect_long1_deps = []
multiselect_long1_link_args = []
multiselect_long1_c_args = []

run_command(gofmt_program, '-w', go_files, check: true)
run_command(goimports_program, '-w', go_files, check: true)
if not fs.is_file('go.mod')
  run_command(go_program, 'mod', 'init', go_name, check: true)
endif
run_command(go_program, 'mod', 'tidy', check: true)
run_command(go_program, 'build', '-o', go_name + '.a', '-buildmode=c-archive', go_files, check: true)

multiselect_long1 = executable(go_name,
     multiselect_long1_srcs,
     dependencies: multiselect_long1_deps,
     include_directories: multiselect_long1_dirs,
     link_args: multiselect_long1_link_args,
     c_args: multiselect_long1_c_args,
     objects: multiselect_long1_objects,
     install: true,
)

