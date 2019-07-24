#!/bin/bash
g++ -pipe -O2 -std=c++11 -o phone_book phone_book.cpp -lm
./phone_book < test.txt 
./phone_book < test.txt > testResult.txt
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


./phone_book < test3.txt 
./phone_book < test3.txt > testResult.txt
echo " "
	
if diff -q "testResult.txt" "test3A.txt"
then
	echo " "
	echo "Success!"
else
	echo " "
	echo "failure"
	diff "testResult.txt" "test3A.txt"
fi

