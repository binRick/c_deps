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



go_path = meson.current_source_dir()
run_command(goimports_program, '-w', go_path + '/' + go_name + '.go', check: true)
if not fs.is_file(go_path + '/go.mod')
  run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod init ' + go_name, go_name, check: true)
endif
run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod tidy', go_name, check: true)
run_command(sh_program, '-c', 'cd ' + go_path + ' && go build -o ' + go_name + '.a' + ' -buildmode=c-archive', check: true)




multiselect_long1 = executable(go_name,
     multiselect_long1_srcs,
     dependencies: multiselect_long1_deps,
     include_directories: multiselect_long1_dirs,
     link_args: multiselect_long1_link_args,
     c_args: multiselect_long1_c_args,
     objects: multiselect_long1_objects,
     install: true,
)

