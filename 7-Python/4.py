import sys
import time
import shutil
import os
import subprocess

print ("\nThis Python script help you to understand how can we use loops\r\n")

raw_input("Press enter to see how to use if-else \n")

if True:
    print "True"
else:
  print "False"
 
 
raw_input("Press enter to see how to use for loop \r\n")
  
#!/usr/bin/python
# Python for loop using range()
 
print "*** Generates a list of 3 values starting from 0 ***\r\n"
for i in range(3):
    print "Welcome",i,"times. \r\n"
 
print "*** Generates a list of 3 values starting from 1 *** \r\n"
for i in range(1,4):
	print "Welcome",i,"times.\r\n"
        
string = "Hello World\r\n"
for x in string:
    print x
    
#!/usr/bin/env python3

n = 100
s = 0
counter = 1
while counter <= n:
    s = s + counter
    counter += 1

print("Sum of 1 until %d: %d \r\n" % (n,s))
        
