#!/bin/sh
format=1.0
board=am335x_evm

bootloader_location=fatfs_boot
dd_spl_uboot_seek=
dd_spl_uboot_bs=
dd_uboot_seek=
dd_uboot_bs=

conf_bootcmd=bootz
boot_script=uEnv.txt
boot_fstype=fat

serial_tty=ttyO0
loadaddr=0x80300000
initrdaddr=0x81600000
zreladdr=0x80008000
fdtaddr=0x815f0000
fdtfile=

usbnet_mem=

