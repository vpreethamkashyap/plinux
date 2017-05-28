#!/bin/bash
# My First Script
clear
path=$(pwd)
cd $path/
echo $path 

while :
do	
	gcc process.c -o pes
	echo
	clear
	echo
	./pes 
	echo	
	echo "press ENTER !!!!!!"
	read proc	
done

