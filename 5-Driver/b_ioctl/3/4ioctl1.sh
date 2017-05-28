clear 
echo
echo "IOCTL Char R/W Driver";
echo
cd drv1
make clean
make
cd ../app
gcc test_ioctlrw.c -o app
cd ..
echo "Press y to run the make or n to come out"
read Var0

if [ "$Var0" = "y" ] || [ "$Var0" = "Y" ]; then 
	cd drv1
	lsmod | grep drv_ioctlrw
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		echo "Removing Node"
		su -c "rmmod drv_ioctlrw.ko"
	else
		echo "Driver is not there";
	fi
		
	echo "Inserting Node"
	su -c "insmod drv_ioctlrw.ko"
fi

lsmod | grep drv_ioctlrw
if [ $? -eq 0 ]; then	
	echo "User is running app"
	cd ../app
	su -c "./app"
	cd ..
	echo "Removing Node"
	su -c "rmmod drv_ioctlrw.ko"
else
	echo "User can't run application Driver is not there";
fi
	
echo "Byeeeeeeee"
echo
