go_name = 'confirm1'
go_files = [
  go_name + '.go',
]
confirm1_srcs = [
  go_name + '.c',
  go_name + '.h',
]
confirm1_objects = [
  go_name + '.a',
]
confirm1_dirs = [
  '.',
]
confirm1_deps = []
confirm1_link_args = []
confirm1_c_args = []

go_path = meson.current_source_dir()
run_command(goimports_program, '-w', go_path + '/' + go_name + '.go', check: true)
if not fs.is_file(go_path + '/go.mod')
  run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod init ' + go_name, go_name, check: true)
endif
run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod tidy', go_name, check: true)
run_command(sh_program, '-c', 'cd ' + go_path + ' && go build -o ' + go_name + '.a' + ' -buildmode=c-archive', check: true)

confirm1 = executable(go_name,
     confirm1_srcs,
     dependencies: confirm1_deps,
     include_directories: confirm1_dirs,
     link_args: confirm1_link_args,
     c_args: confirm1_c_args,
     objects: confirm1_objects,
     install: true,
)

