#!/bin/bash
g++ -pipe -O2 -std=c++11 -o EXE_hash_substring hash_substring.cpp -lm
./EXE_hash_substring < test.txt 
./EXE_hash_substring < test.txt > testResult.txt
echo " "

if diff -q "testResult.txt" "testA.txt"
then
	echo " "
	echo "Success!"
else
	echo " "
	echo "failure"
	diff "testResult.txt" "testA.txt"
fi

