clear 
echo
echo "Kernel Synchronization through MUTEX Lock Driver";
echo
cd drv1
make clean
make
cd ../app
gcc reader.c -o read
gcc writer.c -o write
cd ..	
echo "Press y to insert driver or n to come out"

read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd drv1
	echo "Removing Node"
	lsmod | grep chr_drv_mutex
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod chr_drv_mutex.ko"
	else
		echo "Driver is not there";
	fi
	
	echo "Inserting Node"
	su -c "insmod chr_drv_mutex.ko"
	
	lsmod | grep chr_drv_mutex
	if [ $? -eq 0 ]; then	
		cd ..
		echo "Run application Driver is there";
		x-terminal-emulator -e ./read.sh &
		x-terminal-emulator -e ./write.sh
		echo "Driver is already there";
		su -c "rmmod chr_drv_mutex.ko"
	else
		echo "Unable to Run application Driver is not there";
	fi
fi

echo
echo "Byeeeeeeee"
echo
