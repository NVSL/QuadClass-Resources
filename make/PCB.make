# -*- Makefile -*-
BRD=$(DESIGN).brd
SCH=$(DESIGN).sch
EAGLINT=python $(abspath $(EAGLINT_HOME))/server/eaglint/swoop_lint.py --strict $(CHECKS)
EAGLE_BOM=python $(abspath $(EAGLINT_HOME))/server/eaglint/BOM.py
BOMS=$(patsubst %.sch,%.assembly-bom.html,$(SCH)) $(patsubst %.sch,%.digikey-bom.csv,$(SCH))

.PHONY: all
all:  $(TESTS) $(BOMS)

test: $(TESTS)

.PHONY: %.test
%.test: %.brd %.sch $(LBRS)
	$(EAGLINT) --files $*.brd $*.sch $(LBRS)

CAM_FILE=$(RESOURCES_ROOT)/Eagle/CAM/jlcpcb-4layer-values-eagle9.cam
EAGLE_EXE=/Applications/EAGLE-9.3.0/eagle.app/Contents/MacOS/eagle 

.PHONY: cam
cam: $(DESIGN).cam
%.cam: %.brd
	mkdir -p $@
	$(EAGLE_EXE) -N -X -dCAMJOB -j$(CAM_FILE) -o$@ $<
	mv $@/$@/*.ncd $@/ #unclear why it puts the ncd file here.
	rm -rf $@/$@

%.assembly-bom.html: %.sch
	$(EAGLE_BOM) --sch $^ --mode smds --format html  --out $@

%.digikey-bom.csv: %.sch
	$(EAGLE_BOM) --sch $^ --format csv --out $@

%.cam.zip: %.cam
	(cd $<; zip $(abspath $@) *.{cmp,crm,l1,l2,plc,pls,sol,stc,sts,ncd})

RELEASE_DIR=releases/$(VERSION)
.PRECIOUS: %.cam
.PHONY:release
release: $(BRD) $(SCH) $(LBRS)
	@if ! git diff --exit-code --quiet || ! git diff --quiet --exit-code --cached; then echo "You have uncommitted changes."; exit 1;fi
	@if git rev-parse "$(VERSION)^{tag}" --; then echo "$(VERSION) has already been released"; exit 1; else exit 0; fi
	mkdir -p $(RELEASE_DIR)
	cp $(BRD) $(SCH) $(RELEASE_DIR)
	#python $(EAGLINT_HOME)/server/eaglint/set-attr.py $(RELEASE_DIR)/$(BRD) $(RELEASE_DIR)/$(SCH) --attr 'dict(VERSION="$(VERSION)")'
	$(MAKE) $(RELEASE_DIR)/$(DESIGN).cam.zip
	git add $(RELEASE_DIR)	
	git commit -m "Release $(VERSION)"
	git tag -a $(VERSION) -m "Release $(VERSION)"
	git push origin $(VERSION)

.PHONY: clean
clean:
	rm -rf $(BOMS)
	rm -rf $(CAMDIR).zip
	rm -rf $(CAMDIR)
