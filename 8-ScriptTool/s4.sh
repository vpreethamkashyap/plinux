#!/bin/bash
clear
echo "This script is used to learn various things"
echo

echo "Enter youyr date of birth"
read birthday

today=`date -I`
if test "$birthday" = "$today"
then
	echo "hello happy birthday"
else
	echo "sorry to dissappoint you"
fi

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

set The: unix: operating: system
echo $1
echo $2 
echo $3
echo $4
echo $2

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

var=`cat /etc/passwd`
for i in $var
do 
echo $i
done

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

if [ $(id -u) == "0" ]; then
echo "you are  logged in as a root"
else
echo "you are not logged as a root"
fi

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

for i in 1 
do
a=`wc -l -w< file`
done
echo $a

