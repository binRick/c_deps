tesseract_dep = dependency('tesseract', method: 'pkg-config', required: true)
tesseract_cflags = run_command('pkg-config', '--cflags', 'tesseract',check: true).stdout().strip().split(' ')
tesseract_libs = run_command('pkg-config', '--libs', 'tesseract',check: true).stdout().strip().split(' ')
tesseract_include_path = '/usr/local/include/tesseract'
