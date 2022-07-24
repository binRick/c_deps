go_name = 'multi_select1'
go_files = [
  go_name + '.go',
]
multi_select1_srcs = [
  go_name + '.c',
  go_name + '.h',
]
multi_select1_objects = [
  go_name + '.a',
]
multi_select1_dirs = [
  '.',
]
multi_select1_deps = []
multi_select1_link_args = []
multi_select1_c_args = []

run_command(gofmt_program, '-w', go_files, check: true)
run_command(goimports_program, '-w', go_files, check: true)
if not fs.is_file('go.mod')
  run_command(go_program, 'mod', 'init', go_name, check: true)
endif
run_command(go_program, 'mod', 'tidy', check: true)
run_command(go_program, 'build', '-o', go_name + '.a', '-buildmode=c-archive', go_files, check: true)

multi_select1 = executable(go_name,
     multi_select1_srcs,
     dependencies: multi_select1_deps,
     include_directories: multi_select1_dirs,
     link_args: multi_select1_link_args,
     c_args: multi_select1_c_args,
     objects: multi_select1_objects,
     install: true,
)

