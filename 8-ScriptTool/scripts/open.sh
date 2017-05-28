#!/bin/bash
echo "enter the file name to be opened"
read file_name
#cat $file_name
echo "number of characters in the file is:"
wc -m $file_name
echo "number of lines in the file is:"
wc -l $file_name
echo "number of words in the file is:"
wc -w $file_name
