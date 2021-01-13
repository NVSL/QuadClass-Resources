#-*- Makefile -*-

QUARTER?=wi21
LAB_NAME=$(patsubst %-Solution,%,$(notdir $(PWD)))
STARTER_REPO_NAME=$(LAB_NAME)-Starter-$(QUARTER)
GITHUB_ORG?=UCSD-Quadcopter-Class

.PHONY: build-starter
build-starter:
clean: 

.PHONY: starter
starter:
	#@if ! git diff --exit-code --quiet || ! git diff --quiet --exit-code --cached; then echo "You have uncommitted changes."; exit 1;fi
	rm -rf $@
	mkdir /tmp/$@
	git clone . /tmp/$@/
	mv /tmp/$@ ./
	rm -rf $@/.git
	(cd $@; rm -fr $(SOLUTION_FILES))
	$(MAKE) -f ../Makefile -C $@ build-starter
	@echo Starter files:
	@(cd $@; find .)
	@echo "Create $(GITHUB_ORG)/$(STARTER_REPO_NAME) before pushing"

.PHONY: push-starter-repo
push-starter-repo: 
	$(MAKE) clean
	$(MAKE) starter
	(cd starter; git init; git remote add origin git@github.com:$(GITHUB_ORG)/$(STARTER_REPO_NAME).git)
	(cd starter; git add --force .; git commit -m "Initial import"; git push --set-upstream origin master)

.PHONY: help
help: labs.make.help

.PHONY: labs.make.help
labs.make.help:
	@echo 'make starter           # Prepare starter repo to be pushed for the first time'
	@echo 'make push-starter-repo # Push a starter repo for the first time'
