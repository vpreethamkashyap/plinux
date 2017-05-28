clear 
echo
echo "Asynch Char Driver";
echo
cd drv2
make clean
make
cd ../app
gcc polltest.c -o polltest
gcc writer.c -o write

echo "Press y to insert driver or n to come out"
cd ..
read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd drv2
	echo "Removing Node"
	lsmod | grep chr_drv_poll
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod chr_drv_poll.ko"
	else
		echo "Driver is not there";
	fi
	
	lsmod | grep chr_drv_poll
	if [ $? -eq 0 ]; then	
		echo "Driver is already there Can't Insert";
	else
		echo "Inserting Node"
		su -c "insmod chr_drv_poll.ko"
	fi
	cd ..
		
	lsmod | grep chr_drv_poll
	if [ $? -eq 0 ]; then	
		echo "Run application Driver is there";
		x-terminal-emulator -e ./polltest.sh &
		x-terminal-emulator -e ./write.sh
	else
		echo "Unable to Run application Driver is not there";
	fi
fi


echo
echo "Byeeeeeeee"
echo


