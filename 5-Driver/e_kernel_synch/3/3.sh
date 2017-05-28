clear 
echo
echo "Kernel Synchronization through SPIN Lock Driver";
echo
cd drv3
make clean
make
cd ../app
gcc reader.c -o read
gcc writer.c -o write
echo "Press y to insert driver or n to come out"

read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd ../drv3
	echo "Removing Node"
	lsmod | grep chr_drv_spinlock
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod chr_drv_spinlock.ko"
	else
		echo "Driver is not there";
	fi
	
	echo "Inserting Node"
	su -c "insmod chr_drv_spinlock.ko"
fi

lsmod | grep chr_drv_spinlock
if [ $? -eq 0 ]; then	
	cd ..
	echo "Run application Driver is there";
	x-terminal-emulator -e ./read.sh &
	x-terminal-emulator -e ./write.sh
else
	echo "Unable to Run application Driver is not there";
	cd ..
fi
	
echo
echo "Byeeeeeeee"
echo
