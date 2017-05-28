clear 
echo
echo "Static Char Driver 1";
echo

cd drv
make clean
make
		
cd ../app
gcc app.c -o app
cd  ..	

echo "Press y to run application & insert driver"
read Var0

if [ "$Var0" == "y" ] || [ "$Var0" == "Y" ]; then 
	cd drv
	echo
	lsmod | grep chr_drv_skel
	if [ $? -eq 0 ]; then	
		echo "Driver is already there";
		echo "Driver is removing the node"
		su -c "rmmod chr_drv_skel.ko"
	else
		echo "Driver is not there";
		echo "Driver is inserting the node"
		su -c "insmod chr_drv_skel.ko"
		sudo mknod /dev/char_drv_static c 300 0
		echo "User is running app"
		cd ../app
		echo
		su -c "./app"
	fi
	cd ..
fi

echo 
echo "Byeeeeeeee"
echo

