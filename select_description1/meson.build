go_name = 'select_description1'
go_files = [
  go_name + '.go',
]
select_description1_srcs = [
  go_name + '.c',
  go_name + '.h',
]
select_description1_objects = [
  go_name + '.a',
]
select_description1_dirs = [
  '.',
]
select_description1_deps = []
select_description1_link_args = []
select_description1_c_args = []

if not fs.is_file('go.mod')
  run_command(go_program, 'mod', 'init', go_name, check: true)
endif
run_command(go_program, 'mod', 'tidy', check: true)
run_command(go_program, 'build', '-o', go_name + '.a', '-buildmode=c-archive', go_files, check: true)

select_description1 = executable(go_name,
     select_description1_srcs,
     dependencies: select_description1_deps,
     include_directories: select_description1_dirs,
     link_args: select_description1_link_args,
     c_args: select_description1_c_args,
     objects: select_description1_objects,
     install: true,
)

