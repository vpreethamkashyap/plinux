clear 
echo
echo "mytasklet Driver";
echo
cd drv
make clean
make
cd ../app
gcc inttest.c -o inttest
 
echo "Press y to insert driver or n to come out"
cd ..
read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd drv
	echo "Removing Node"
	lsmod | grep mytasklet
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod mytasklet.ko"
	else
		echo "Driver is not there";
	fi
	
	lsmod | grep mytasklet
	if [ $? -eq 0 ]; then	
		echo "Driver is already there Can't Insert";
	else
		echo "Inserting Node"
		su -c "insmod mytasklet.ko"
	fi
	cd ..
		
	lsmod | grep mytasklet
	if [ $? -eq 0 ]; then	
		echo "Run application Driver is there";
		x-terminal-emulator -e ./inttest.sh
	else
		echo "Unable to Run application Driver is not there";
	fi
fi


echo
echo "Byeeeeeeee"
echo


