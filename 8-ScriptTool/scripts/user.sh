#!/bin/bash

Echo "Do you want to Add a User Y|N"
Read option

While [ $option = Y ]

Do
		Echo "Enter the Username"
		Read name

		`cut -d ":" -f1 /etc/passwd > /home/file`
		Usercount=`cat /home/file | wc -l`

	For w in $usercount
	
	Do	
		val=`sed -n ''$w'p' /home/file`

		if [ "$name == $val" ]

			then 
				echo "User already Exists"
			else
				useradd $name
				echo useradded
				passwd $name
				
		fi
				usercount=$(($usercount-1))

	done
	echo " if u want to add another user if yes press Y else N"
	read option 
done
