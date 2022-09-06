if fs.is_dir('.git')
    git_rev_parse = run_command(git_program, 'rev-parse', '--short', '@', check: true)
    git_sha = git_rev_parse.stdout().strip()
else
    git_sha = ''
endif
