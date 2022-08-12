BASHFUL_RUN=$(PASSH) $(BASHFUL) run
BASHFUL_EXTRACT_UNTRACKED_FILES=sed -n '/^Untracked files.*$$/,/^[[:space:]]*$$/p'|grep -v 'to include in'|tr '^[[:blank:]]' ' '

bashful-pre:
	@$(ANSI) --save-palette
	@$(KFC) -p vscode
	@$(ANSI) --hide-cursor
	@clear

bashful-extract-untracked-files:

bashful-post:
	@$(ANSI) -n --show-cursor
	@$(ANSI) --restore-palette

bashful-clean: bashful-pre do-bashful-clean bashful-post
bashful-tidy: bashful-pre do-bashful-tidy bashful-post
bashful-build: bashful-pre do-bashful-build bashful-post
bashful-muon-build: bashful-pre do-bashful-muon-build bashful-post
bashful-git-status: bashful-pre bashful-rm-git-status-logs do-bashful-git-status bashful-post bashful-view-repo-files
bashful-git-diff: bashful-pre do-bashful-git-diff bashful-post
bashful-build-commands: bashful-pre do-bashful-build-commands bashful-post
bashful-test-commands: bashful-pre do-bashful-test-commands bashful-post
bashful-test: bashful-pre do-bashful-test bashful-post
bashful-view-git-diff: bashful-pre do-bashful-view-git-diff bashful-post

bashful-bat-modified-files-logs:
	@$(BAT) /tmp/meson-repos-modified-files-*.log 2>/dev/null||true
bashful-rm-modified-files-logs:
	@$(RM) /tmp/meson-repos-modified-files-*.log 2>/dev/null||true

bashful-bat-git-status-logs:
	@$(BAT) /tmp/meson-repos-git-status-*.log 2>/dev/null||true
bashful-rm-git-status-logs:
	@$(RM) /tmp/meson-repos-git-status-*.log 2>/dev/null||true

do-bashful-clean:
	@$(BASHFUL_RUN) --tags clean etc/meson-repos.yaml
do-bashful-tidy:
	@$(BASHFUL_RUN) --tags tidy etc/meson-repos.yaml
do-bashful-muon-build:
	@$(BASHFUL_RUN) --tags build etc/muon-repos.yaml
do-bashful-build:
	@$(BASHFUL_RUN) --tags build etc/meson-repos.yaml
do-bashful-build-commands:
	@$(BASHFUL_RUN) --tags build-commands etc/meson-repos-info.yaml
do-bashful-test-commands:
	@$(BASHFUL_RUN) run --tags test-commands etc/meson-repos-info.yaml
do-bashful-test:
	@$(PASSH) -L /tmp/meson-repos-do-test.log bashful run --tags test etc/meson-repos.yaml
do-bashful-modified-files:
	@$(PASSH) -L /tmp/meson-repos-do-modified-files.log bashful run --tags modified-files etc/meson-repos-info.yaml
do-bashful-git-status:
	@$(BASHFUL) run --tags git-status etc/meson-repos-info.yaml
do-bashful-git-diff:
	@$(PASSH) -L /tmp/meson-repos-do-git-diff.log bashful run --tags git-diff etc/meson-repos-info.yaml
	@$(MAKE) -B do-bashful-view-git-diff

bashful-view-repo-files:
	@~/repos/c_deps/scripts/view-repo-files.sh|bat --style=plain

do-bashful-view-git-diff:
	@$(PASSH) $(BAT) --style=full /tmp/meson-repos-git-diff-*.log
do-bashful-view-modified-files:
	@$(PASSH) $(BAT) --style=full /tmp/meson-repos-modified-files-*.log
do-bashful-view-git-status:
	@$(PASSH) $(BAT) --style=full /tmp/meson-repos-git-status-*.log

bashful: bashful-pre do-bashful-tidy do-bashful-clean do-bashful-build do-bashful-test bashful-post
