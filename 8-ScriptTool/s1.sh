#!/bin/bash

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
echo "Script used to airthmatic operations in different ways"
x=4 
y=5
let sum=$x+$y
echo "The sum of constant variables = $sum "

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
echo
echo "Enter one number"
read a
echo "Enter another number"
read b

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
sum=$(($a+$b))
echo "Sum by using () braces = $sum"
echo

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
sum=$[$a + $b]
echo "Sum by using [] braces = $sum"
echo

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
sum=`expr $a + $b`
echo "Sum by using '' single quotes = $sum"
echo


echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
let sum=$a+$b
echo "Sum by using let = $sum"
echo

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
declare -i a=20 c=5
declare -i b=30
declare -i sum
sum=$a+$c
echo $sum
