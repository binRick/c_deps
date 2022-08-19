
fmt-scripts:
	@$(SHFMT) -w scripts/*.sh 2>/dev/null||true

uncrustify:
	@$(ANSI) --green Uncrustify
	@$(FIND) -L $(TIDIED_FILES) -type f -maxdepth 3| $(SORT) -u|$(XARGS) -P 10 -I {} $(UNCRUSTIFY) -c ~/repos/c_deps/etc/uncrustify.cfg --replace "{}" 

uncrustify-clean:
	@$(ANSI) --yellow Clean Uncrustify Cruft Files
	@$(FIND) -L . -type f -name "*unc-back*" -maxdepth 3|$(XARGS) -I % $(REALPATH) % | $(SORT) -u|$(XARGS) -P 10 -I % $(UNLINK) % 2>/dev/null ||true

fix-dbg:
	@$(ANSI) --yellow Fix dbg spacing
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
	@if [[ -d scripts ]]; then $(FIND) scripts/*.sh -type f >/dev/null||true && $(MAKE) fmt-scripts||true; fi
	@true

do-tidy: uncrustify uncrustify-clean shfmt
	@$(MAKE) fix-dbg||true
tidy: do-tidy
