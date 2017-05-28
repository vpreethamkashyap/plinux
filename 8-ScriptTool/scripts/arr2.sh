#!/bin/bash
ARRAY=(one two three)
echo ${ARRAY[*]}
echo ${ARRAY[2]}
ARRAY[3]=four
echo ${ARRAY[*]}
unset ARRAY[1]
echo ${ARRAY[*]}
echo ${#ARRAY}
