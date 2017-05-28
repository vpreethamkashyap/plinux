# All case statements are defined here .... ........

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

echo "enter yes or no"
read select
case $select in
	y|Y|YES|yes) echo u selected yes;;
	n|N|no|NO) echo u selected no;;
	*) echo select yes or no;;
esac

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

echo -e  "1) a \n 2) b \n 3) c \n 4) d \n 5) e" 
echo "select any one:"
read var1
case $var1 in

a)	echo  options are
		echo -e  "1) a1 \n 2)a2 \n 3)a3 enter"
		read var2
		case $var2 in
			a1) echo "`ls`";;
			a2) echo "`pwd`";;
			a3) echo "`ls -l /home`";;
			*) echo default ;;
		esac
		;;
b) 	echo "case two selected";;
c) 	echo "case  three selected";;
*) 	echo default ;;
esac

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
while :
do
	clear
	echo "-------------------------------------"
	echo " Main Menu "
	echo "-------------------------------------"
	echo "[1] Show Todays date/time"
	echo "[2] Show files in current directory"
	echo "[3] Show calendar"
	echo "[4] Start editor to write letters"
	echo "[5] Exit/Stop"
	echo "======================="
	echo -n "Enter your menu choice [1-5]: "
	read yourch
	case $yourch in
		1) 	echo "Today is `date` , press a key. . ." ; read ;;
		2) 	echo "Files in `pwd`" ; ls -l ; echo "Press a key. . ." ; read ;;
		3)	cal; echo "press a key ...";read;;
		4) 	vi ;;
		5)	break ;;
		*) 	echo "Opps!!! Please select choice 1,2,3,4, or 5";
		echo "Press a key. . ." ; read ;;
	esac
done

echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"

echo -e  "1) a \n 2) b \n 3) c \n 4) d " 
echo "select any one:"
read a
case $a in
a) echo -e "enter either a1 or a2 or a3"
	read a1
	case $a1 in
		a1) echo "one";;
		a2) echo "two";;
		a3) echo "three";;
	esac
	;;
b) echo "case two selected";;
c) echo "case  three selected";;
*) 	echo "Opps!!! Please select choice a, b, c, d";
esac


echo
echo "Enter"
read enter
clear
echo  "************************************************************"
echo  "************************************************************"
echo "enter a number"
read num
while [ $num -ne 0 ]
do
	rev=$(($num % 10))
	num=$(($num / 10))
	echo -n "$rev"
done




