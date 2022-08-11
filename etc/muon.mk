muon-setup:
	@$(MUON) setup muon-build
muon-build:
	@$(MUON) samu -C build-muon
muon-install:
	@cd build-muon && $(MUON) install
muon-test:
	@cd build-muon && $(MUON) test
muon: muon-setup muon-build muon-test
