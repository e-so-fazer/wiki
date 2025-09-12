#!/bin/bash

set -e
SOLUTION=$1
BASENAME=$(basename "$SOLUTION" .cpp)
g++ -std=c++20 -O2 -Wall "$SOLUTION" -o sol

for infile in ${BASENAME}_input*.txt; do
	num=${infile#${BASENAME}_input}   # strip "basename_input"
    num=${num%.txt}                   # strip ".txt"
    outfile="${BASENAME}_output${num}.txt"

    echo "Running test case #$num"
    ./sol < "$infile" > user_out.txt

    if diff -wB -Z user_out.txt "$outfile" > /dev/null; then
        echo "Test #$num passed"
    else
        echo "Test #$num failed"
        echo "Input:"
        cat "$infile"
        echo
        echo "Expected output:"
        cat "$outfile"
        echo
        echo "Your output:"
        cat user_out.txt
        exit 1
    fi
done
