
.PHONY: starter-repo
starter-repo:
	#@if ! git diff --exit-code --quiet || ! git diff --quiet --exit-code --cached; then echo "You have uncommitted changes."; exit 1;fi
	rm -rf starter
	mkdir /tmp/starter
	git clone . /tmp/starter/
	mv /tmp/starter ./
	rm -rf starter/.git
	(cd starter; rm -fr $(SOLUTION_FILES))
	find starter
