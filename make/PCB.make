# -*- Makefile -*-
BRD=$(DESIGN).brd
SCH=$(DESIGN).sch
EAGLINT=eaglelint  --strict $(CHECKS) #python $(abspath $(EAGLINT_HOME))/server/EagleLint/swoop_lint.py
EAGLE_BOM=python $(abspath $(EAGLINT_HOME))/eaglint/BOM.py
BOMS=$(patsubst %.sch,%.assembly-bom.html,$(SCH)) $(patsubst %.sch,%.digikey-bom.csv,$(SCH))
CAMS=$(DESIGN).cam $(DESIGN).cam.zip $(DESIGN).stencil  $(DESIGN).stencil.zip
VERSION?=$(cat VERSION.txt)
BOM_QTY?=5

FULL_VERSION=$(DESIGN)-$(VERSION)
.PHONY: all
all:  $(TESTS) $(BOMS) $(CAMS)

test: $(TESTS)

.PHONY: hooks
hooks:
	git config core.hooksPath $(RESOURCES_ROOT)/githooks/


.PHONY: %.test
%.test: %.brd %.sch $(LBRS)
	$(EAGLINT) --files $*.brd $*.sch $(LBRS)

CAM_FILE=$(RESOURCES_ROOT)/Eagle/CAM/jlcpcb-4layer-values-eagle9.cam
STENCIL_CAM_FILE=$(RESOURCES_ROOT)/Eagle/CAM/jlcpcb-stencil.cam
EAGLE_EXE=/Applications/EAGLE-9.3.0/eagle.app/Contents/MacOS/eagle 

.PHONY: cam
cam: $(DESIGN).cam $(DESIGN).stencil

.PRECIOUS: %.cam 
%.cam: %.brd
	mkdir -p $@
	$(EAGLE_EXE) -N -X -dCAMJOB -j$(CAM_FILE) -o$@ $<
	mv $@/$@/*.ncd $@/ #unclear why it puts the ncd file here.

%.stencil: %.brd
	mkdir -p $@
	$(EAGLE_EXE) -N -X -dCAMJOB -j$(STENCIL_CAM_FILE) -o$@ $<
	rm -rf $@/$@

%.assembly-bom.html: %.sch
	$(EAGLE_BOM) --sch $^ --mode smds --format html  --out $@

.PHONY: bom
bom: $(DESIGN).digikey-bom.csv

%.digikey-bom.csv: %.sch
	$(EAGLE_BOM) --sch $^ --format csv --out $@  --qty $(BOM_QTY)

%.cam.zip: %.cam
	(cd $<; zip $(abspath $@) *.{cmp,crm,l1,l2,plc,pls,sol,stc,sts,ncd})

.PRECIOUS: %.stencil
%.stencil.zip: %.stencil
	(cd $<; zip $(abspath $@) *.crm)

RELEASE_DIR=releases/$(VERSION)
.PHONY:release
release: $(BRD) $(SCH) $(LBRS)
	@if ! git diff --exit-code --quiet || ! git diff --quiet --exit-code --cached; then echo "You have uncommitted changes."; exit 1;fi
	@if git rev-parse "$(FULL_VERSION)^{tag}" --; then echo "$(FULL_VERSION) has already been released"; exit 1; else exit 0; fi
	mkdir -p $(RELEASE_DIR)
	cp $(BRD) $(SCH) $(RELEASE_DIR)
	#python $(EAGLINT_HOME)/server/eaglint/set-attr.py $(RELEASE_DIR)/$(BRD) $(RELEASE_DIR)/$(SCH) --attr 'dict(VERSION="$(FULL_VERSION)")'
	$(MAKE) $(RELEASE_DIR)/$(DESIGN).cam.zip $(RELEASE_DIR)/$(DESIGN).stencil.zip
	$(MAKE) $(RELEASE_DIR)/$(DESIGN).digikey-bom.csv
	#false
	git add $(RELEASE_DIR)	
	git commit -m "Release $(FULL_VERSION)"
	git tag -a $(FULL_VERSION) -m "Release $(FULL_VERSION)"
	git push origin $(FULL_VERSION)

.PHONY: clean
clean:
	rm -rf $(BOMS)
	rm -rf $(DESIGN).cam.zip
	rm -rf $(DESIGN).stencil.zip
	rm -rf $(DESIGN).cam
	rm -rf $(DESIGN).stencil

.PHONY: help
help: PCB.make.help

.PHONY: PCB.make.help
PCB.make.help:
	@echo 'make hooks   # install git hooks'
	@echo 'make cam     # build cam files'
	@echo 'make bom     # build bom files'
	@echo 'make release # create a release'
