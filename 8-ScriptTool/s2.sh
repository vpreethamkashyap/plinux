#!/bin/bash
clear
echo "This script is used to take backup of folder by using tar command"
echo
echo "tar cvf Destination_Path Source_Path"
echo
TIME=`date +"%b-%d-%y"`             			# This Command will add date in Backup File Name.
BACKUP_FILENAME="backup_$TIME.tgz"     		# Here i define Backup file name format.


tar -zcvf ~/mylinux/$BACKUP_FILENAME ~/mylinux/ARM


echo "You can even un tar the zip file"
echo " tar -xzvf filename.zip -C destination_directory"
echo 
tar -zxvf ~/mylinux/$BACKUP_FILENAME



