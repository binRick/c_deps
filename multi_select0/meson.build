go_name = 'multi_select0'
go_files = [
  go_name + '.go',
]
multi_select0_srcs = [
  go_name + '.c',
  go_name + '.h',
]
multi_select0_objects = [
  go_name + '.a',
]
multi_select0_dirs = [
  '.',
]
multi_select0_deps = []
multi_select0_link_args = []
multi_select0_c_args = []

if not fs.is_file('go.mod')
  run_command(go_program, 'mod', 'init', go_name, check: true)
endif
run_command(go_program, 'mod', 'tidy', check: true)
run_command(go_program, 'build', '-o', go_name + '.a', '-buildmode=c-archive', go_files, check: true)

multi_select0 = executable(go_name,
     multi_select0_srcs,
     dependencies: multi_select0_deps,
     include_directories: multi_select0_dirs,
     link_args: multi_select0_link_args,
     c_args: multi_select0_c_args,
     objects: multi_select0_objects,
     install: true,
)

