go_name = 'multiselect-long0'
go_files = [
  go_name + '.go',
]
multiselect_long0_srcs = [
  go_name + '.c',
  go_name + '.h',
]
multiselect_long0_objects = [
  go_name + '.a',
]
multiselect_long0_dirs = [
  '.',
]
multiselect_long0_deps = []
multiselect_long0_link_args = []
multiselect_long0_c_args = []

run_command(gofmt_program, '-w', go_files, check: true)
run_command(goimports_program, '-w', go_files, check: true)
if not fs.is_file('go.mod')
  run_command(go_program, 'mod', 'init', go_name, check: true)
endif
run_command(go_program, 'mod', 'tidy', check: true)
run_command(go_program, 'build', '-o', go_name + '.a', '-buildmode=c-archive', go_files, check: true)

multiselect_long0 = executable(go_name,
     multiselect_long0_srcs,
     dependencies: multiselect_long0_deps,
     include_directories: multiselect_long0_dirs,
     link_args: multiselect_long0_link_args,
     c_args: multiselect_long0_c_args,
     objects: multiselect_long0_objects,
     install: true,
)

