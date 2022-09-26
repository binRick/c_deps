leptonica_dep = dependency('lept', method: 'pkg-config', required: true)
leptonica_cflags = run_command('pkg-config', '--cflags', 'lept',check: true).stdout().strip().split(' ')
leptonica_libs = run_command('pkg-config', '--libs', 'lept',check: true).stdout().strip().split(' ')
