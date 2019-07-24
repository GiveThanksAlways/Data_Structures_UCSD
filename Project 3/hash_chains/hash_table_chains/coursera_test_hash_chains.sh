#!/bin/bash
g++ -pipe -O2 -std=c++11 -o hash_chains hash_chains.cpp -lm
./hash_chains < test1.txt 
./hash_chains < test1.txt > testResult.txt
echo " "

if diff -q "testResult.txt" "test1A.txt"
then
	echo "----------- "
	echo "Success!"
    echo "----------- "
else
	echo " "
	echo "failure"
	diff --side-by-side "testResult.txt" "test1A.txt"
    echo " "
fi



