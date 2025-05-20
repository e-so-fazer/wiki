LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds KACTL (KTH Algorithm Competition Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build Wiki, quickly (only runs LaTeX once)"
	@echo "	make wiki		- to build Wiki"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove kactl.pdf"
	@echo "	make test		- to run all the stress tests in stress-tests/"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""
	@echo "For more information see the file 'doc/README'"

fast: | build
	$(LATEXCMD) content/wiki.tex </dev/null
	cp build/wiki.pdf wiki.pdf

wiki: test-session.pdf | build
	$(LATEXCMD) content/wiki.tex && $(LATEXCMD) content/wiki.tex
	cp build/wiki.pdf wiki.pdf

clean:
	cd build && rm -rf wiki.aux wiki.log wiki.tmp wiki.toc wiki.pdf wiki.ptc snippets

veryclean: clean
	rm -f wiki.pdf test-session.pdf

.PHONY: help fast wiki clean veryclean snippets

build:
	mkdir -p build/

test:
	./doc/scripts/run-all.sh .

snippets:
	mkdir -p build/snippets/cpp/
	./doc/scripts/snippet-all.sh .

test-compiles:
	./doc/scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
