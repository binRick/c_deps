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


go_path = meson.current_source_dir()
run_command(goimports_program, '-w', go_path + '/' + go_name + '.go', check: true)
if not fs.is_file(go_path + '/go.mod')
  run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod init ' + go_name, go_name, check: true)
endif
run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod tidy', go_name, check: true)
run_command(sh_program, '-c', 'cd ' + go_path + ' && go build -o ' + go_name + '.a' + ' -buildmode=c-archive', check: true)



select_description1 = executable(go_name,
     select_description1_srcs,
     dependencies: select_description1_deps,
     include_directories: select_description1_dirs,
     link_args: select_description1_link_args,
     c_args: select_description1_c_args,
     objects: select_description1_objects,
     install: true,
)

