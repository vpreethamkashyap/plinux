#!/bin/bash

clear
echo "*****************************************************************************"
echo "*****************************************************************************"
echo "This script is used for if-else"

#String Comparison 	Description
#Str1 = Str2 	Returns true if the strings are equal
#Str1 != Str2 	Returns true if the strings are not equal
#-n Str1 	Returns true if the string is not null
#-z Str1 	Returns true if the string is null


echo "Enter String 1"
read Str1

echo "Enter String 2"
read Str2

if [ $Str1 =  $Str2 ]; then
	echo "Strings are equal"
elif [ $Str1 !=  $Str2 ]; then
	echo "Strings are not equal"
fi



#Numeric Comparison 	Description
#expr1 -eq expr2 	Returns true if the expressions are equal
#expr1 -ne expr2 	Returns true if the expressions are not equal
#expr1 -gt expr2 	Returns true if expr1 is greater than expr2
#expr1 -ge expr2 	Returns true if expr1 is greater than or equal to expr2
#expr1 -lt expr2 	Returns true if expr1 is less than expr2
#expr1 -le expr2 	Returns true if expr1 is less than or equal to expr2
#! expr1 	Negates the result of the expression

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

echo "Type any number to check grater than 10 or not "
read Number1

if [ $Number1 > 10 ]; then
	echo "Number is greater than 10"
elif [ $Number1 < 10 ]; then
	echo "Number is less than 10"
fi

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

echo "Type any number to compare with previous number"
read Number2

if [ $Number1 -eq $Number2 ]; then
	echo "Both numbers are equal"
fi

if [ $Number1 -ne $Number2 ]; then
	echo "Both numbers are not equal"
fi

if [ $Number1 -gt $Number2 ]; then
	echo "Number 1 > Number 2"
fi

if [ $Number1 -ge $Number2 ]; then
	echo "Number 1 >= Number 2"
fi

if [ $Number1 -lt $Number2 ]; then
	echo "Number 1 < Number 2"
fi

if [ $Number1 -le $Number2 ]; then
	echo "Number 1 <= Number 2"
fi

#File Conditionals 	Description
#-d file 	True if the file is a directory
#-e file 	True if the file exists (note that this is not particularly portable, thus -f is generally used)
#-f file 	True if the provided string is a file
#-g file 	True if the group id is set on a file
#-r file 	True if the file is readable
#-s file 	True if the file has a non-zero size
#-u 	True if the user id is set on a file
#-w 	True if the file is writable

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

echo "Enter the file name which exist in current folder"
echo
echo "Enter the name of the file"
 read file_name
 	if [ ! -f $file_name ]
  then
		echo "$file_name dose not exist"
	elif [ ! -r $file_name ]
	then
		echo "The file dose not have read permission"
	elif [ ! -w $file_name ]
	then
		echo "The file dose not have write permission"
	elif [ -f $file_name -a -r $file_name ] # -a is logical AND
	then
		echo "The file is OK"
fi

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

if test -e new
then
echo "file exist"
else
touch new
fi

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

var1="Testing"
var2=12345
var3=6.789
printf "var1 is %10.5s \n" $var1
printf "var1 is %7.7s and \n " $var1
printf "var2 is %9.6e \n" $var2
printf "var3 is $%05.2f \n" $var3

echo "Press Enter"
read key
clear
echo "*****************************************************************************"
echo "*****************************************************************************"

declare -i sum
declare -i c=1 
declare -i d=2
declare -i e 
a=10
b=20
echo `expr $a + $b `
sum=$a+$b
echo $sum
echo $[ $a + $b]
echo $(($a+$b))
e=c+d
echo $e

