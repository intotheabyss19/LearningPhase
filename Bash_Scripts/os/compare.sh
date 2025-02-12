#! usr/bin/bash

read -p "Enter the value of a: " a
read -p "Enter the value of b: " b

if [ $a -gt $b ]; then
	echo "$a is greater than $b"
elif [ $a -eq $b ]; then
	echo "$a is equal to $b"
else
	echo "$a is smaller than $b"
fi
