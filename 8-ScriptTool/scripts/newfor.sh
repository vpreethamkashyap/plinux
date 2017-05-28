#!/bin/bash
sum=0
for var in $1 $2 $3 $4 $5
do
sum=$(($sum + $var))
done
echo "sum is $sum"
