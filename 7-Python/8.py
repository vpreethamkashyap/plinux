#!/usr/bin/python

import sys
import time
import shutil
import os
import subprocess

#Accessing Values in Tuples:
tup1 = ('physics', 'chemistry', 1997, 2000);
tup2 = (1, 2, 3, 4, 5, 6, 7 );
print "tup1[0]: ", tup1[0]
print "tup2[1:5]: ", tup2[1:5]


#Updating Tuples
tup1 = (12, 34.56);
tup2 = ('abc', 'xyz');

# Following action is not valid for tuples
# tup1[0] = 100;
# So let's create a new tuple as follows
tup3 = tup1 + tup2;
print tup3


#Delete Tuple Elements
tup = ('physics', 'chemistry', 1997, 2000);
print tup
del tup;
print "After deleting tup : "
print tup

#No Enclosing Delimiters
print 'abc', -4.24e93, 18+6.6j, 'xyz'
x, y = 1, 2;
print "Value of x , y : ", x,y

#Built-in Tuple Functions

#cmp(tuple1, tuple2)
#Compares elements of both tuples.
tuple1, tuple2 = (123, 'xyz'), (456, 'abc')
print cmp(tuple1, tuple2)
print cmp(tuple2, tuple1)
tuple3 = tuple2 + (786,);
print cmp(tuple2, tuple3)	

#len(tuple)
#Gives the total length of the tuple.
tuple1, tuple2 = (123, 'xyz', 'zara'), (456, 'abc')
print "First tuple length : ", len(tuple1)
print "Second tuple length : ", len(tuple2)

#max(tuple)
#Returns item from the tuple with max value.
tuple1, tuple2 = (123, 'xyz', 'zara', 'abc'), (456, 700, 200)
print "Max value element : ", max(tuple1)
print "Max value element : ", max(tuple2)	

#min(tuple)
#Returns item from the tuple with min value.
tuple1, tuple2 = (123, 'xyz', 'zara', 'abc'), (456, 700, 200)
print "min value element : ", min(tuple1)
print "min value element : ", min(tuple2)	

#tuple(seq)
#Converts a list into tuple.
aList = (123, 'xyz', 'zara', 'abc');
aTuple = tuple(aList)
print "Tuple elements : ", aTuple

