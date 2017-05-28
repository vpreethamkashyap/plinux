clear 
echo
echo "Static Char Driver";
echo
cd ChardevType0
make clean
make
gcc app.c -o app
echo "Driver is removing the node"
su -c "rmmod chr_drv_skel.ko"
echo "Driver is inserting the node"
su -c "insmod chr_drv_skel.ko"
sudo mknod /dev/sample_cdrv c 300 0
echo "User is running app"
su -c "./app"
