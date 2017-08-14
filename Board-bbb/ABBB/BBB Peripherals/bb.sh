clear

echo "*********************************************"
echo "*********************************************"
echo "Type key from 1 to 6 "
echo "Enter 1 to set up the cross compiler"
echo "Enter 2 to set up Bootloader: U-Boot"
echo "Enter 3 to set up Linux Kernel"
echo "Enter 4 to set up Root File System"
echo "Enter 5 to set up "
echo "Enter 6 to set up "

read var

echo "ARM Cross Compiler: GCC"

function Func_call_1
{
	wget -c https://releases.linaro.org/14.09/components/toolchain/binaries/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux.tar.xz
	tar xf gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux.tar.xz
	export CC=`pwd`/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-
}

function Func_call_2
{
	git clone git://git.denx.de/u-boot.git
	cd u-boot/
	git checkout v2015.07 -b tmp
	wget -c https://rcn-ee.com/repos/git/u-boot-patches/v2015.07/0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch
	patch -p1 < 0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch
	make ARCH=arm CROSS_COMPILE=${CC} distclean
	make ARCH=arm CROSS_COMPILE=${CC} am335x_evm_defconfig
	make ARCH=arm CROSS_COMPILE=${CC}
	cd ..
}

function Func_call_3
{
	git clone https://github.com/RobertCNelson/bb-kernel
	cd bb-kernel/
	git checkout origin/am33x-v4.1 -b tmp
	./build_kernel.sh
}


function Func_call_4
{
	wget -c https://rcn-ee.com/rootfs/eewiki/minfs/ubuntu-14.04.2-minimal-armhf-2015-06-09.tar.xz
	md5sum ubuntu-14.04.2-minimal-armhf-2015-06-09.tar.xz
	e8653a3db794437fcde6247abfd0d361  ubuntu-14.04.2-minimal-armhf-2015-06-09.tar.xz
	tar xf ubuntu-14.04.2-minimal-armhf-2015-06-09.tar.xz
}

function Func_call_5
{
}

function Func_call_6
{
}

case $var in
1) echo "calling test 1"; Func_call_1 ;;
2) echo "calling test 2"; Func_call_2 ;;
3) echo "calling test 3"; Func_call_3 ;;
4) echo "calling test 4"; Func_call_4 ;;
5) echo "calling test 5"; Func_call_5 ;;
6) echo "calling test 6"; Func_call_6 ;;
*) echo "You have choosed a wrong option" ;
esac
