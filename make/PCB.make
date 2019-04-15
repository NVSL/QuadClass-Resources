# -*- Makefile -*-
BRD=$(DESIGN).brd
SCH=$(DESIGN).sch
EAGLINT=eaglelint  --strict $(CHECKS) #python $(abspath $(EAGLINT_HOME))/server/EagleLint/swoop_lint.py
EAGLE_BOM=python $(abspath $(EAGLINT_HOME))/server/eaglint/BOM.py
BOMS=$(patsubst %.sch,%.assembly-bom.html,$(SCH)) $(patsubst %.sch,%.digikey-bom.csv,$(SCH))

.PHONY: all
all:  $(TESTS) $(BOMS)

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
cam: $(DESIGN).cam
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

%.digikey-bom.csv: %.sch
	$(EAGLE_BOM) --sch $^ --format csv --out $@

%.cam.zip: %.cam
	(cd $<; zip $(abspath $@) *.{cmp,crm,l1,l2,plc,pls,sol,stc,sts,ncd})

%.stencil.zip: %.stencil
	(cd $<; zip $(abspath $@) *.crm)

RELEASE_DIR=releases/$(VERSION)
.PRECIOUS: %.cam
.PHONY:release
release: $(BRD) $(SCH) $(LBRS)
	@if ! git diff --exit-code --quiet || ! git diff --quiet --exit-code --cached; then echo "You have uncommitted changes."; exit 1;fi
	@if git rev-parse "$(VERSION)^{tag}" --; then echo "$(VERSION) has already been released"; exit 1; else exit 0; fi
	mkdir -p $(RELEASE_DIR)
	cp $(BRD) $(SCH) $(RELEASE_DIR)
	#python $(EAGLINT_HOME)/server/eaglint/set-attr.py $(RELEASE_DIR)/$(BRD) $(RELEASE_DIR)/$(SCH) --attr 'dict(VERSION="$(VERSION)")'
	$(MAKE) $(RELEASE_DIR)/$(DESIGN).cam.zip $(RELEASE_DIR)/$(DESIGN).stencil.zip
	git add $(RELEASE_DIR)	
	git commit -m "Release $(VERSION)"
	git tag -a $(VERSION) -m "Release $(VERSION)"
	git push origin $(VERSION)

.PHONY: clean
clean:
	rm -rf $(BOMS)
	rm -rf $(CAMDIR).zip
	rm -rf $(CAMDIR)
