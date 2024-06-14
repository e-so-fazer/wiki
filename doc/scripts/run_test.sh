#!/usr/bin/env bash
test="$1"
failTests=""
ulimit -s 524288 # For 2-sat test

echo "$(basename $test): "
start=`date +%s.%N`
g++ -Wall -fsanitize=address,undefined -g -Wfatal-errors -Wconversion -std=c++17 -O2 $test && ./a.out
retCode=$?
if (($retCode != 0)); then
	echo "Failed with $retCode"
	fail+=1
	failTests="$failTests$test\n"
else
	echo "Success"
fi
end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )
echo "Took $runtime seconds"
rm -f a.out
