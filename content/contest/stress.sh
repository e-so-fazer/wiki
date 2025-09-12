#!/bin/bash
set -e
SOLUTION=$1
BRUTE=$2
GEN=$3

g++ -std=c++17 -O2 -Wall "$SOLUTION" -o sol
g++ -std=c++17 -O2 -Wall "$BRUTE" -o brute
g++ -std=c++17 -O2 -Wall "$GEN" -o gen

MAX_TESTS=10000

for ((t=1; t<=MAX_TESTS; t++)); do
    echo "Running test #$t"
    ./gen > in.txt
    ./sol < in.txt > out_sol.txt
    ./brute < in.txt > out_bf.txt

    if ! diff -ZB out_sol.txt out_bf.txt > /dev/null; then
        echo "X Mismatch found on test #$t"
        echo "Input:"
        cat in.txt
        echo
        echo "Solution output:"
        cat out_sol.txt
        echo
        echo "Bruteforce output:"
        cat out_bf.txt
        exit 1
    fi
done

echo "All $MAX_TESTS tests passed!"
# ./stress_test.sh sol.cpp brute.cpp gen.cpp
