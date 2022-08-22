TIDIED_FILES ?=*/*.c */*.h

get-tidied-files-lines-qty:
	@wc -l < $(shell $(MAKE) -B get-tidied-files)|grep total|tail -n1|tr -s ' '|cut -d' ' -f2
get-tidied-files-qty:
	@$(MAKE) -B get-tidied-files|wc -l
get-tidied-files:
	@$(FIND) -L $(TIDIED_FILES) -type f -maxdepth 3| $(SORT) -u

fmt-scripts:
	@$(SHFMT) -w scripts/*.sh 2>/dev/null||true

uncrustify:
	@make -B get-tidied-files|$(XARGS) -P 10 -I {} $(UNCRUSTIFY) -c ~/repos/c_deps/etc/uncrustify.cfg --replace "{}" 2>/dev/null||true

uncrustify-clean:
	@$(FIND) -L . -type f -name "*unc-backup*" -maxdepth 3|$(XARGS) -I % $(REALPATH) % | $(SORT) -u|$(XARGS) -P 10 -I % $(UNLINK) % 2>/dev/null ||true

fix-dbg:
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
	@if [[ -d scripts ]]; then $(FIND) scripts/*.sh -type f >/dev/null 2>&1 && $(MAKE) -B fmt-scripts 2>/dev/null||true; fi
	@true

do-tidy: 
	@$(MAKE) -B uncrustify uncrustify-clean shfmt fix-dbg 2>/dev/null||true

get-tidied-files-stats:
	  @printf "%s files, %s lines\n" "$(shell make -B get-tidied-files-qty)" "$(shell make -B get-tidied-files-lines-qty)"

do-timed-tidy: 
	@ts=`$(DATE) +%s%3N` && \
	  $(ANSI) --yellow "Uncrustifying $(shell make -B get-tidied-files-stats)" && \
		$(MAKE) -B do-tidy >&2 && \
		end_ts=`$(DATE) +%s%3N` && \
		$(ANSI) --up=1 -n --green  "Uncrustified  $(shell make -B get-tidied-files-stats) in " && \
		bc <<< `printf "%s-%s" "$$end_ts" "$$ts"`|tr -d '\n' && \
		ansi --blue ms && sleep 1

tidy:
	@passh $(MAKE) -B do-timed-tidy
