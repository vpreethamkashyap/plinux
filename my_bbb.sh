############################################# u-boot ###############################################
####################################################################################################

git clone git://git.denx.de/u-boot.git && cd u-boot
git pull
git branch -a
git checkout -b {Give the branch name here}

make distclean
u-boot$ patch -p1 <  0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch 
make am335x_boneblack_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

####################################################################################################
############################## Kernel ##############################################################

git clone https://github.com/beagleboard/linux.git
git branch -a
git checkout -b origin/4.4

make mrproper
sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bb.org_defconfig
sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- uImage dtbs LOADADDR=0x82000000 -j8
sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules
sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules_install INSTALL_MOD_PATH=KERNEL_MODULES/

make ARCH=arm oldconfig


preetham@ubuntu:~/beagleboneblack/linux/arch/arm/boot$ pwd
/home/preetham/beagleboneblack/linux/arch/arm/boot
preetham@ubuntu:~/beagleboneblack/linux/arch/arm/boot$ sudo cp -vr am335x-boneblack.dtb uImage /media/preetham/20ac8006-5328-48a7-ac07-1193505819d1/boot/
[sudo] password for preetham: 
am335x-boneblack.dtb -> '/media/preetham/20ac8006-5328-48a7-ac07-1193505819d1/boot/am335x-boneblack.dtb
uImage -> /media/preetham/20ac8006-5328-48a7-ac07-1193505819d1/boot/uImage
preetham@ubuntu:~/beagleboneblack/linux/arch/arm/boot$ 

############################################################################################################

############################# for creating root fs ##########################################################

  999  sync
 1000  sudo tar -xvf ubuntu-16.04.3-minimal-armhf-2017-12-09.tar.xz 
 1001  ls
 1002  cd ubuntu-16.04.3-minimal-armhf-2017-12-09/
 1003  ls
 1004  sudo tar -xvf armhf-rootfs-ubuntu-xenial.tar 
 1005  sync
root@ubuntu:/media/preetham/20ac8006-5328-48a7-ac07-1193505819d1# cd ubuntu-16.04.3-minimal-armhf-2017-12-09
root@ubuntu:/media/preetham/20ac8006-5328-48a7-ac07-1193505819d1# mv * ../

loadaddr=0x82000000
fdtaddr=0x88000000
mmcroot=/dev/mmcblk0p2 rw;
mmcrootfstype=ext4 rootwait;
uenvcmd=run loaduimage;run loadfdt; run mmcargs; bootm ${loadaddr} - ${fdtaddr};
mmcargs=setenv bootargs console=${console} root=${mmcroot} rootfstype=${mmcrootfstype} ${optargs} selinux=0
loadfdt=ext2load mmc ${mmcdev}:2 ${fdtaddr} /boot/${fdtfile};
loaduimage=ext2load mmc 0:2 ${loadaddr} /boot/uImage;

####################################################################################################
################################### Boot arguments in u-boot side ##################################

setenv mmcroot "/dev/mmcblk0p2 rw"
setenv mmcrootfstype "ext2 rootwait"
setenv mmcargs 'setenv bootargs console=${console} ${optargs} root=${mmcroot} init=/bin/bash'
run mmcargs
setenv loadfdt "ext2load mmc ${mmcdev}:2 ${fdtaddr} /boot/am335x-boneblack.dtb"
setenv loaduimage "ext2load mmc 0:2 ${loadaddr} /boot/uImage"
setenv loadzimage "ext2load mmc 0:2 ${loadaddr} /boot/zImage"
run loaduimage
run loadfdt
setenv bbb "run mmcargs; run loaduimage; run loadfdt; bootm ${loadaddr} - ${fdtaddr}"
setenv bbz "run mmcargs; run loadzimage; run loadfdt; bootm ${loadaddr} - ${fdtaddr}"
saveenv
run bbb

setenv tmmcroot "/dev/mmcblk0p2 rw"
setenv tmmcrootfstype "ext2 rootwait"
setenv tmmcargs 'setenv bootargs console=${console} ${optargs} root=${mmcroot} init=/bin/bash'
setenv tloadfdt "ext2load mmc ${mmcdev}:2 ${fdtaddr} /boot/am335x-boneblack.dtb"
setenv tloaduimage "ext2load mmc 0:2 ${loadaddr} /boot/uImage"
setenv bbb "run tmmcargs; run tloaduimage; run tloadfdt; bootm ${loadaddr} - ${fdtaddr}"
run bbb

#################################################################################################
################## RootFs ubuntu download from here #############################################
http://www.armhf.com/boards/beaglebone-black/bbb-sd-install/

set the scp 
#################################################################################################
##############################On Board installation #################################################################################################

sudo apt-get update
sudo apt-get install python
sudo apt-get install i2c-tools
sudo apt-get install python-smbus
sudo apt-get install python-serial 
sudo apt-get install python-setuptools 
sudo apt-get install python-dev 
sudo apt-get install python-pip



# To start work on UART

# First check in your log file demsg | grep tty*
# What are the  tty are available it can be ttyO1 or ttyS1 
# First check that your minicom is connected to which minicom UART 
# if series start with ttyS means ttyS1 to S5
# if series start with ttyO means ttyO1 to O5
# if tty are not enable in dtb that is user responsibility to enable the tty in DTB file.


####################################################################################################################
								Uart python script
uart pins for 1 

pinmux_uart1_pins {
	pinctrl-single,pins = <0x180 0x30 0x184 0x0>;
	linux,phandle = <0x2c0>;
	phandle = <0x2c0>;
};


####################################################################################################################
import serial
import time
import datetime
import re
data=0
ser = serial.Serial("/dev/ttyO1", baudrate=115200)
while True:
	while (ser.inWaiting() > 0):
		data = ser.read()
		ser.write(data)      
	  	print("%c ")% data



# To start work on I2C

####################################################################################################################
								I2c Script 
####################################################################################################################

import smbus
import time
bus = smbus.SMBus(2)
address = 0x50
regmsbyte = 0x00
reglsbyte = 0x06
# Write word using the 24LC256's Byte Write operation

bus.write_byte_data(address,regmsbyte,reglsbyte)
lsbyte = bus.read_byte(address)
msbyte = bus.read_byte(address)

regmsbyte = 0x04   #this register used to select the page addres 00 01 02 03 04 05 06 07
 
reglsbyte = 0x20   # this register cain helpo user to select the register on particular page 

datalsbyte = 0x21
datamsbyte = 0x71

writestring = [reglsbyte, datalsbyte, datamsbyte]

# Read word using the 24LC256's Random Read operation

bus.write_byte_data(address,regmsbyte,reglsbyte)
bus.write_i2c_block_data(address,regmsbyte,writestring)

print("datalsbyte = 0x%x \n")% lsbyte
print("datamsbyte = 0x%x \n")% msbyte

####################################################################################################################

i2cdetect -l
root@ubuntu-armhf:/sys/bus/i2c/devices# i2cdetect -y -r 2
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: 50 -- -- -- UU UU UU UU -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --                         
root@ubuntu-armhf:/sys/bus/i2c/devices# 


i2cset -y 2 0x50 0x00 0x00; i2cdump -y 2 0x50 c;
i2cset -y 2 0x50 0x11; 
i2cset -y 2 0x50 0x00 0x00; i2cget -y 2 0x50 0x00 w;


root# wget https://raw.github.com/dgallot/i2c-tools/master/eepromer/eeprom.c
i2cdump -y -r 0x00-0x06 2 0x50 c
i2cget -y 2 0x50 0x00
i2cset -y 2 0x50 0x00 0x10
i2cset -y 2 0x50 0x00 0x10 0x29
i2cset -y 2 0x50 0x00 0x00; i2cget -y 2 0x50 0x00 w
i2cdump -y 2 0x50 w

i2cget -f -y I2CBUS CHIP-ADDRESS DATA-ADDRESS MODE
i2cget -f -y 2 0x50 0x000 w

i2cset -f -y I2CBUS CHIP-ADDRESS DATA-ADDRESS VALUE MODE
i2cset -f -y 2 0x50 0x020 0x0040 w

i2cget -y 1 0x22 0x00 w
i2cset -y 2 0x50 0x00 0x1E w
i2cset -y 2 0x50 0x15 0x78


i2cset -y 2 0x50 0x00 0x00 0x1234;i2cset -y 2 0x50 0x00 0x00;
i2cset -y 2 0x50 0x00 0x00; i2cget -y 2 0x50 0x00 w


root@ubuntu-armhf:/home/ubuntu# i2cset -y 2 0x50 0x00 0x20; i2cdump -y 2 0x50 c                                                                   
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f    0123456789abcdef
00: 61 c3 ff ff ff ff ff ff ff ff ff ff ff ff ff ff    a?..............
10: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
20: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
30: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
40: 00 ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
50: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
60: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
70: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
80: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
90: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
a0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
b0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
c0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
d0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
e0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
f0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
root@ubuntu-armhf:/home/ubuntu# i2cset -y 2 0x50 0x00 0x10; i2cdump -y 2 0x50 c                                                                   
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f    0123456789abcdef
00: 61 c3 ff ff ff ff 71 53 ff ff ff ff ff ff ff ff    a?....qS........
10: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
20: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
30: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
40: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
50: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
60: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
70: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
80: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
90: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
a0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
b0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
c0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
d0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
e0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................
f0: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff    ................

This is for selecting the Page here 

i2cset -y 2 0x50 0x00 0x00; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x01; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x02; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x03; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x04; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x05; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x06; i2cdump -y 2 0x50 c 
i2cset -y 2 0x50 0x00 0x06; i2cdump -y 2 0x50 c 

#####################################################################################################################
									GPIO Script 
#####################################################################################################################

#####################################################################################################################
									CAN Script 
#####################################################################################################################

					pinmux_can1_pins {
						pinctrl-single,pins = <0x180 0x12 0x184 0x32>;
						linux,phandle = <0x2c2>;
						phandle = <0x2c2>;
					};
					
					can@481d0000 {
						compatible = "ti,am3352-d_can";
						ti,hwmods = "d_can1";
						reg = <0x481d0000 0x2000>;
						clocks = <0x3c>;
						clock-names = "fck";
						syscon-raminit = <0x3 0x644 0x1>;
						interrupts = <0x37>;
						status = "okay";
						pinctrl-names = "default";
						pinctrl-0 = <0x2c2>;
						linux,phandle = <0xab>;
						phandle = <0xab>;
					};
					
		
					
http://www.thomas-wedemeyer.de/beaglebone-canbus-python.html

root@ubuntu-armhf:~# sudo ip link set can0 up type can bitrate 500000 
root@ubuntu-armhf:~# sudo ifconfig can0 up
root@ubuntu-armhf:~# git clone https://github.com/linux-can/can-utils.git
root@ubuntu-armhf:~# sudo apt-get install automake
root@ubuntu-armhf:~# sudo apt-get install autoconf
root@ubuntu-armhf:~# sudo apt-get install libtool
root@ubuntu-armhf:~# cd can-utils/
root@ubuntu-armhf:~# ./autogen.sh
root@ubuntu-armhf:~# ./configure
root@ubuntu-armhf:~# make

Sending a CAN-message to the adress 0x5a1 with the databyte[0..5]=0,1,2,3,4
./cansend can0 5A1#00.01.02.03.04 

To log the messages on the CAN Bus you can use the CAN Dump program:
./candump can0



########################################################################################
sudo apt-get install lighttpd

########################################################################################

					user_leds_s0 {
						pinctrl-single,pins = <0x54 0x7 0x58 0x17 0x5c 0x7 0x60 0x17>;
						phandle = <0x49>;
					};


