do-muon-setup:
	@muon setup build-muon
do-muon-build:
	@muon samu -C build-muon
do-muon-install:
	@cd build-muon && muon install
do-muon-test:
	@cd build-muon && muon test
build-muon: do-muon-setup do-muon-build
do-muon: do-muon-setup do-muon-build
muon: build-muon do-muon-test
