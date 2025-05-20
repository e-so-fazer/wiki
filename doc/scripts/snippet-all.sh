#!/usr/bin/env bash
DIR=${1:-.}

echo $DIR
tests="$(find $DIR/content -name '*.h')"
declare -i pass=0
declare -i fail=0
failTests=""
ulimit -s 524288 # For 2-sat test
for test in $tests; do
	name=$(basename "$test")
	out_name="${name%.*}.snippets"
	python3 $DIR/doc/scripts/gen_snippets.py -i $test -o $DIR/build/snippets/cpp/$out_name

done
echo "SUCESS: Snippets generated"
