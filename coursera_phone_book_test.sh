#!/bin/bash
g++ -pipe -O2 -std=c++11 -o phone_book phone_book.cpp -lm
./phone_book < test.txt 
./phone_book < test.txt > testResult.txt
if diff -q "testResult.txt" "testA.txt"
then
	echo " "
	echo "Success!"
else
	echo " "
	echo "failure"
	diff "testResult.txt" "testA.txt"
fi

