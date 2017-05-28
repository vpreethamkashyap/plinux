clear 
echo
echo "Dynamic Char Driver";
echo
cd drv
make clean
make

cd ../app
gcc app.c -o app
cd  ..	

echo "Press y to run the make or n to come out"
read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 

	cd drv	
	lsmod | grep chr_drv_dynamic
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";	
		echo "Driver is removing the node";
		su -c "rmmod chr_drv_dynamic.ko"
	else
		echo "Driver is not there";
	fi
	
	echo "Driver is inserting the node";
	su -c "insmod chr_drv_dynamic.ko"
	#sudo mknod /dev/chardrv_dynamic c 249 0
	echo "User is running app";
	cd ../app
	echo
	su -c "./app"
	cd ..
fi

echo 
echo "Byeeeeeeee";
echo
