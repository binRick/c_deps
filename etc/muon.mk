MUON_BUILD_DIR=build-muon
MUON_PARALLEL_COMMANDS=5
muon-setup:
	@$(MUON) setup $(MUON_BUILD_DIR)
muon-build:
	@$(MUON) samu -C $(MUON_BUILD_DIR) -j $(MUON_PARALLEL_COMMANDS)
muon-install:
	@cd $(MUON_BUILD_DIR) && $(MUON) install
muon-test:
	@cd $(MUON_BUILD_DIR) && $(MUON) test
muon: 
	@make -B muon-setup muon-build
