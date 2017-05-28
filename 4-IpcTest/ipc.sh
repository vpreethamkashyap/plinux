#!/bin/bash
# My First Script
clear
path=$(pwd)
cd $path/
echo $path 

function ipc()
{
	echo
	echo "This Scripts test all the IPC as per user selection";
	echo " User has to Select Below option";
	echo " Press c to clear Screen";
	echo " Press 1 for PIPE Test";
	echo " Press 2 for FIFO Test";
	echo " Press 3 for MESSAGE Test";
	echo " Press 4 for SHARED MEMORY Test";
	echo " Press 5 for Socket Test";
	echo " Press 6 to exit";
	echo
}

function TestShm()
{
	echo "Shared Memory test started";
	cd shm
	gcc shmwrite.c -o shmw
	gcc shmread.c -o shmr
	./shmw  
	./shmr
	cd ..
	echo "Press key to come out from test";
	read var
	echo "************* BYE *******************";
}

function TestSocket()
{
	echo "Socket test started";
	cd socket
	gcc tcpclient.c -o tcl
	gcc tcpserver.c -o tsv
	./tsv &	gnome-terminal -x ./tcl
	cd ..
	echo "Press key to come out from test";
	read var
	echo "************* BYE *******************";
}

function TestPipes()
{
	echo "Pipes test started";
	cd pipes
	gcc PipeTest.c -o pipes
	./pipes
	cd ..
	echo;
	echo "Press key to come out from test";
	read var
	echo "************* BYE *******************";
}

function TestFifos()
{
	echo "Fifo's test started";
	cd fifos
	
	gcc Fifoserver.c -o fserver
	gcc Fifoclient.c -o fclient
	./fserver &	./fclient		#gnome-terminal -x 
	cd ..
	echo;
	echo "Press key to come out from test";
	read var
	echo "************* BYE *******************";
}

function TestMess()
{
	echo "Mesaages test started";
	cd mes
	gcc MesTx.c -o mestx
	gcc MesRx.c -o mesrx
	./mestx  # &	gnome-terminal -x 
	./mesrx
	cd ..
	echo;
	echo "Press key to come out from test";
	read var
	echo "************* BYE *******************";
}

while :
do
	ipc
  read yourch
	case $yourch in
	
	 'c') clear;;
	 
	 1) TestPipes;;
	 
	 2) TestFifos;;
	 
	 3)	TestMess;;
	 
	 4) TestShm;;
	 
	 5) TestSocket;;
	 
	 6) exit 0;;
	 
	 *) echo "Opps!!! Please select choice 1,2,3,4, or 5";
					 echo "Press a key. . ." ; read ;;
	esac
done



