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


go_path = meson.current_source_dir()
run_command(goimports_program, '-w', go_path + '/' + go_name + '.go', check: true)
if not fs.is_file(go_path + '/go.mod')
  run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod init ' + go_name, go_name, check: true)
endif
run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod tidy', go_name, check: true)
run_command(sh_program, '-c', 'cd ' + go_path + ' && go build -o ' + go_name + '.a' + ' -buildmode=c-archive', check: true)


multiselect_long0 = executable(go_name,
     multiselect_long0_srcs,
     dependencies: multiselect_long0_deps,
     include_directories: multiselect_long0_dirs,
     link_args: multiselect_long0_link_args,
     c_args: multiselect_long0_c_args,
     objects: multiselect_long0_objects,
     install: true,
)

