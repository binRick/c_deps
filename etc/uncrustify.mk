
fmt-scripts:
	@shfmt -w scripts/*.sh

uncrustify:
	@ansi --green Uncrustify
	@find -L $(TIDIED_FILES) -type f -maxdepth 3| $(SORT) -u|xargs -P 10 -I {} $(UNCRUSTIFY) -c ~/repos/c_deps/etc/uncrustify.cfg --replace "{}" 

uncrustify-clean:
	@ansi --yellow Clean Uncrustify Cruft Files
	@find -L . -type f -name "*unc-back*" -maxdepth 3|xargs -I % realpath % | $(SORT) -u|xargs -P 10 -I % $(UNLINK) % 2>/dev/null ||true

fix-dbg:
	@ansi --yellow Fix dbg spacing
	@$(SED)   's|, %[[:space:]].*u);|, %u);|g'  -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*i);|, %i);|g'  -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*h);|, %h);|g'  -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*c);|, %c);|g'  -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*s);|, %s);|g'  -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*ld);|, %ld);|g' -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*lld);|, %lld);|g' -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*d);|, %d);|g'  -i $(TIDIED_FILES)
	@$(SED)   's|, %[[:space:]].*zu);|, %zu);|g' -i $(TIDIED_FILES)

shfmt:
	@if [[ -d scripts ]]; then find scripts/*.sh -type f >/dev/null||true && make fmt-scripts||true; fi
	@true

do-tidy: uncrustify uncrustify-clean shfmt
	@make fix-dbg||true
tidy: do-tidy
