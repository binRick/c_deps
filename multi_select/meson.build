go_name = 'multi_select'
go_files = [
  go_name + '.go',
]
multi_select_srcs = [
  go_name + '.c',
  go_name + '.h',
]
multi_select_objects = [
  go_name + '.a',
]
multi_select_dirs = [
  '.',
]
multi_select_deps = []
multi_select_link_args = []
multi_select_c_args = []


go_path = meson.current_source_dir()
run_command(goimports_program, '-w', go_path + '/' + go_name + '.go', check: true)
if not fs.is_file(go_path + '/go.mod')
  run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod init ' + go_name, go_name, check: true)
endif
run_command(sh_program, '-c', 'cd ' + go_path + ' && go mod tidy', go_name, check: true)
run_command(sh_program, '-c', 'cd ' + go_path + ' && go build -o ' + go_name + '.a' + ' -buildmode=c-archive', check: true)



multi_select = executable(go_name,
     multi_select_srcs,
     dependencies: multi_select_deps,
     include_directories: multi_select_dirs,
     link_args: multi_select_link_args,
     c_args: multi_select_c_args,
     objects: multi_select_objects,
     install: true,
)

