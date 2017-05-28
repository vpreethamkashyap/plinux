echo "enter two names"
read s1 s2
name="$s1 $s2"
echo $name

echo " current command line args are \$1=$1,\$2=$2,\$3=$3"
shift
echo " after shift command line args are \$1=$1,\$2=$2,\$3=$3"

echo

for a in `seq 80`  # or   for a in $( seq 80 )
# Same as   for a in 1 2 3 4 5 ... 80   (saves much typing!).
# May also use 'jot' (if present on system).
do
  echo -n "$a "
done      # 1 2 3 4 5 ... 80
# Example of using the output of a command to generate 
# the [list] in a "for" loop.
echo; 


OPTIONS="Hello Quit"
select opt in $OPTIONS; do
	 if [ "$opt" = "Quit" ]; then
		 echo done
		 exit
	 elif [ "$opt" = "Hello" ]; then
		 echo Hello World
	 else
		 clear
		 echo bad option
		 break;
	 fi
done

PS3="Choose (1-5):"
echo "Choose from the list below."
select name in red green blue yellow magenta
do
    break
done
echo "You chose $name."
