gcc shmread.c 	-o shr
gcc shmwrite.c 	-o shw

su -c "./shw & ./shr"
