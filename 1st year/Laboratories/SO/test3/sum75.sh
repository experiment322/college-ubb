#!/bin/bash
sum=0
while [ $sum -lt 75 ]; do
	read n
	let "sum+=n"
done
echo $sum
