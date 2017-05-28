#My first script

clear
echo "if you want to make press y"
read String
if [ "$String" == "y" ] || [ "$String" =="Y" ];then
	echo "make clean all"
	make clean all
fi

sudo ./entity
