#!/bin/bash

# For LOOP

echo "For Loops"
for num in 1 2 3 4 5
	do
		echo $num
	done

x=11
for((i=6;$i<$x;i=$i+1))
	do
		echo $i
		sleep 1
	done

echo "While Loops"

# While loop

echo "Enter y: "
read y
j=1
sum=0
while [ $j -le $y ]
	do
		sum=`expr $sum+$j`
		j=`expr $j+1`
		echo "Sum is: $[sum]"
	done
