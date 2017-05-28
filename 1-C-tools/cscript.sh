clear

echo "*********************************************"
echo "*********************************************"
echo "Type key from 1 to 6 "
read var

function Func_call_test_1
{
	echo "*********************************************"
	echo "*********************************************"
	echo 
	gcc -o test_binary  c1.c
	./test_binary
}

function Func_call_test_2
{
	echo "*********************************************"
	echo "*********************************************"
	echo 
	gcc -o test_binary  c2.c
	./test_binary
}

function Func_call_test_3
{
	echo "*********************************************"
	echo "*********************************************"
	echo 
	gcc -o test_binary  c3.c
	./test_binary
}

function Func_call_test_4
{
	echo "*********************************************"
	echo "*********************************************"
	echo 
	gcc -o test_binary  c4.c

	while :
	do
			echo "Please type the argument from 1 to 15"
			echo "Type 0 to come out"
			read arg
			if [ $arg -eq 0 ]; then
				break;
			else
					./test_binary $arg
			fi			
	done
}

function Func_call_test_5
{
	echo "*********************************************"
	echo "*********************************************"
	echo 
	gcc -o test_binary  c5.c
	./test_binary
}

function Func_call_test_6
{
	echo "*********************************************"
	echo "*********************************************"
	echo 
	gcc -o test_binary  c6.c
	./test_binary "arg1" "arg2" "arg3" "arg4"
}

case $var in
1) echo "calling test 1"; Func_call_test_1 ;;
2) echo "calling test 2"; Func_call_test_2 ;;
3) echo "calling test 3"; Func_call_test_3 ;;
4) echo "calling test 4"; Func_call_test_4 ;;
5) echo "calling test 5"; Func_call_test_5 ;;
6) echo "calling test 6"; Func_call_test_6 ;;
*) echo "You have choosed a wrong option" ;
esac
