#!/bin/bash
clear
echo "This script is used to learn loops"
echo


#various for loops

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
for i in 1 2 3 4 5
do
   echo "Welcome $i times"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
for i in {1..5}
do
   echo "New Welcome $i times"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
for i in $(seq 1 2 20)
do
   echo "Welcome $i times"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
for (( c=1; c<=5; c++ ))
do
   echo "Welcome $c times"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
i=1
for day in Mon Tue Wed Thu Fri
do
 echo "Weekday $((i++)) : $day"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
i=1
weekdays="Mon Tue Wed Thu Fri"
for day in $weekdays
do
 echo "Weekday $((i++)) : $day"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
i=1
for day
do
 echo "Weekday $((i++)) : $day"
done

echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"
for i in $( ls )
do
echo item: $i
done


echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
for (( a = 0; a <10; a++))
do
	echo "Value of a is $a"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
for file in /etc/*
do
	if [ "${file}" == "/etc/resolv.conf" ]
	then
		countNameservers=$(grep -c nameserver /etc/resolv.conf)
		echo "Total  ${countNameservers} nameservers defined in ${file}"
		break
	fi
done

