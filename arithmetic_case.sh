#!/bin/bash
echo "Enter two numbers: "
read a b
echo "Enter 1.Add 2.Substract 3.Multiply 4.Divide 5.Exit."

echo "Enter your choice: "
read n

case $n in

1)
n3=`expr $a+$b`
echo "Addition of $[a] and $[b] is $[n3]"
;;

2)
3=n3=`expr $a-$b`
echo "Substraction of $[a] and $[b] is $[n3]"
;;

3)
n3=`expr $a*$b`
echo "Multiplication of $[a] and $[b] is $[n3]"
;;

4)
n3=`expr $a/$b`
echo "Division of $[a] and $[b] is $[n3]"
;;
esac
