gcc Fifoserver.c -o fserver
gcc Fifoclient.c -o fclient

su -c "./fserver & ./fclient"
