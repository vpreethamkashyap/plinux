clear 
echo
echo "IOCTL Char Driver";
echo
cd drv1
make clean
make
cd ../app
gcc test_ioctl.c -o app
cd ..
echo "Press y to run the make or n to come out";
read Var0
echo
echo "you have pressed $Var0 ";
if [ "$Var0" = "y" ]; then 
	cd drv1
	echo "Driver is removing the node"
	lsmod | grep chr_drv_ioctl
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		su -c "rmmod chr_drv_ioctl.ko"
	else
		echo "Driver is not there";
	fi
	echo "Driver is inserting the node"
	su -c "insmod chr_drv_ioctl.ko"
fi

dmesg | tail

lsmod | grep chr_drv_ioctl
if [ $? -eq 0 ]; then	
	#sudo mknod /dev/my_toctl c 249 0
	echo "User is running app"
	echo 
	echo "/************************************************************/"
	cd ../app
	su -c "./app"
	cd ..
	echo "Driver is already there";
	su -c "rmmod chr_drv_ioctl.ko"
else
	cd ../
	echo "User can't run application Driver is not there";
fi

echo "Byeeeeeeee"
echo
