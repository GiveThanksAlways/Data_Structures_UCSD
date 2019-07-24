#!/bin/bash
g++ -pipe -O2 -std=c++11 -o EXE_is_bst is_bst.cpp -lm
./EXE_is_bst < test.txt 
./EXE_is_bst < test.txt > testResult.txt
echo " "

if diff -q "testResult.txt" "testA.txt"
then
	echo " "
	echo "Success!"
else
	echo " "
	echo "\"YOU SHALL NOT PASS\" -Gandolf"
	echo " " 
	diff "testResult.txt" "testA.txt"
fi

