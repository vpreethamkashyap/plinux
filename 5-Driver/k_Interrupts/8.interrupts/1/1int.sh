clear 
echo
echo "interrupt Driver";
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
	lsmod | grep interrupt
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod interrupt.ko"
	else
		echo "Driver is not there";
	fi
	
	lsmod | grep interrupt
	if [ $? -eq 0 ]; then	
		echo "Driver is already there Can't Insert";
	else
		echo "Inserting Node"
		su -c "insmod interrupt.ko"
	fi
	cd ..		
fi


echo
echo "Byeeeeeeee"
echo

# cat /proc/interrupts 
#lspci -v



