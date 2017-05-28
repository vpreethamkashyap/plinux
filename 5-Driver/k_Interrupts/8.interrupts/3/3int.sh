clear 
echo
echo "hrexamp Driver";
echo
cd drv
make clean
make
 
 
echo "Press y to insert driver or n to come out"
cd ..
read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd drv
	echo "Removing Node"
	lsmod | grep hrexamp
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod hrexamp.ko"
	else
		echo "Driver is not there";
	fi
	
	lsmod | grep hrexamp
	if [ $? -eq 0 ]; then	
		echo "Driver is already there Can't Insert";
	else
		echo "Inserting Node"
		su -c "insmod hrexamp.ko"
	fi
	cd ..
fi


echo
echo "Byeeeeeeee"
echo


