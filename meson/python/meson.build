python_program = find_program('python', required : true)
python3_program = find_program('python3', required : true)
pip_program = find_program('pip', required : true)
python_config_program = find_program('python-config', required : true)
cython_program = find_program('cython', required : true)
stickytape_program = find_program('stickytape', required : true)


python_inc = run_command(python_config_program, '--include', check: true).stdout().strip().split(' ')
python_cflags = run_command(python_config_program, '--cflags', check: true).stdout().strip().split(' ')
python_ldflags = run_command(python_config_program, '--ldflags', check: true).stdout().strip().split(' ')


