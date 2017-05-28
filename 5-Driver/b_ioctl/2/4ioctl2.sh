clear 
echo
echo "IOCTL Char var Driver";
echo
cd drv2
make clean
make
cd ../app
gcc test_ioctlvar.c -o app
cd ..
echo "Press y to run the make or n to come out"
read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd drv2
	echo "Removing Node"
	lsmod | grep drv_ioctlvar
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod drv_ioctlvar.ko"
	else
		echo "Driver is not there";
	fi
	echo "Inserting Node"
	su -c "insmod drv_ioctlvar.ko"
	
	lsmod | grep drv_ioctlvar
	if [ $? -eq 0 ]; then	
		echo "User is running app"
		echo 
		echo "/************************************************************/";
		cd ../app
		su -c "./app"
		cd ..		
		echo "Removing Node"
		lsmod | grep drv_ioctlvar
		if [ $? -eq 0 ]; then	
			echo "Driver is already there";
			su -c "rmmod drv_ioctlvar.ko"
		else
			echo "Driver is not there";
		fi	
	else
		echo "User can't run application Driver is not there";
	fi
fi

echo "Byeeeeeeee"
echo
