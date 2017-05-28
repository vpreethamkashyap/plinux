# All functions statements are defined here .... ........

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

function add()
{
	c=`expr $1 + $2`
	echo $c
}
add 2 3

echo
echo "Enter"
read enter
echo  "************************************************************"
echo  "************************************************************"

function quit
{
	exit
}
function emy 
{
	echo $1 $2 $3
}

emy Hello hai df
emy World
echo $1
read enter
clear

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

function quit 
{
	echo "I am exiting"
}

function add 
{
	c=`expr $1 + $2`
	echo $c
}

function hello 
{
	echo "Hello!! the operation is completed"
	add 2 4
	quit
}
hello
