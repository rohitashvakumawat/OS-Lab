#!/bin/bash
echo "Enter two numbers: "
read a b
echo "Enter\n1.Add\n2.Substract\n3.Multiply\n4.Divide\n5.Exit."
echo "Enter your choice: "
read n
if [[ $n -eq 1 ]]
then
n3=`expr $a+$b`
echo "Addition of $[a] and $[b] is $[n3]"
elif [[ $n -eq 2 ]]
then
3=n3=`expr $a-$b`
echo "Substraction of $[a] and $[b] is $[n3]"
elif [[ $n -eq 3 ]]
then
n3=`expr $a*$b`
echo "Multiplication of $[a] and $[b] is $[n3]"
elif [[ $n -eq 4 ]]
then
n3=`expr $a/$b`
echo "Division of $[a] and $[b] is $[n3]"
fi
