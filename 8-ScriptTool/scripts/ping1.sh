#!/bin/bash
#inorder to see whether the host(ip) is alive or notalive
for host in $* 
do
ping -c5 $host &> /dev/null
if [ $? = 0 ]; then
printf "%-30s is alive \n " $host
else
printf "%-30s is not alive \n" $host
fi
done
