
scc:
	@$(SCC) \
		--no-gen \
		--no-duplicates \
		--no-gitignore \
		--no-large \
		--no-size \
		-f wide \
		--by-file \
		--large-line-count 7000 \
		--exclude-dir build,build-muon,submodules,subprojects,.venv,site-packages,tmp,.attic,.src,vendor,tmp,wrapdb,embeds,embedded \
		--include-ext c,h,build,Makefile,sh,mk

