#various while loops

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
LIMIT=19
a=0

while [ "$a" -le "$LIMIT" ]
do
	let a++
	if [ "$a" -gt 2 ]
	then
		break  # Skip entire rest of loop.
	fi
	echo Value "$a"
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

COUNTER=0
while [ $COUNTER -lt 10 ]
 do
echo "the counter is $COUNTER"
let COUNTER=COUNTER+1
done

echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
y=1
while [ $y -le 12 ]; do
		x=1
		while [ $x -le 12 ]; do
						printf "% 4d" $(( $x * $y ))
						let x++
		done
		echo ""
		let y++
done


echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
COUNTER=20
until [ $COUNTER -lt 10 ]
do 
echo COUNTER $COUNTER
let COUNTER-=1
done

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
while getopts "abc"  var
do
	case $var in
	a) echo service network $var;;
	b) echo service network $var;;
	c) echo service network $var;;
	*) echo  wrong usage;;
	esac
done

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

while getopts  "abc:" flag
do
  echo "$flag" $OPTIND $OPTARG
done
