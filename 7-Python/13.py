#!/usr/bin/python

import sys
import time
import shutil
import os
import subprocess

########################################################################
#The raw_input Function

#!/usr/bin/python

str = raw_input("Enter your input: ");
print "Received input is : ", str


########################################################################
#The input Function
#!/usr/bin/python

str = input("Enter your input: ");
print "Received input is : ", str


########################################################################

# Open a file
fo = open("foo.txt", "wb")
print "Name of the file: ", fo.name
print "Closed or not : ", fo.closed
print "Opening mode : ", fo.mode
print "Softspace flag : ", fo.softspace

########################################################################
#The close() Method
#!/usr/bin/python

# Open a file
fo = open("foo.txt", "wb")
print "Name of the file: ", fo.name

# Close opend file
fo.close()

########################################################################
#Reading and Writing Files
#!/usr/bin/python

# Open a file
fo = open("foo.txt", "wb")
fo.write( "Python is a great language.\nYeah its great!!\n");

# Close opend file
fo.close()

########################################################################
#The read() Method
#!/usr/bin/python

# Open a file
fo = open("foo.txt", "r+")
str = fo.read(10);
print "Read String is : ", str
# Close opend file
fo.close()

########################################################################
#File Positions
#!/usr/bin/python

# Open a file
fo = open("foo.txt", "r+")
str = fo.read(10);
print "Read String is : ", str

# Check current position
position = fo.tell();
print "Current file position : ", position

# Reposition pointer at the beginning once again
position = fo.seek(0, 0);
str = fo.read(10);
print "Again read String is : ", str
# Close opend file
fo.close()

########################################################################
#Renaming and Deleting Files
#!/usr/bin/python
import os

# Rename a file from test1.txt to test2.txt
os.rename( "test1.txt", "test2.txt" )

########################################################################
#The remove() Method
import os

# Delete file test2.txt
os.remove("text2.txt")

########################################################################
#
#!/usr/bin/python
import os

# Create a directory "test"
os.mkdir("test")

########################################################################
#The chdir() Method
import os

# Changing a directory to "/home/newdir"
os.chdir("/home/newdir")

########################################################################
#The getcwd() Method
#!/usr/bin/python
import os

# This would give location of the current directory
os.getcwd()

########################################################################
#
#!/usr/bin/python
import os

# This would  remove "/tmp/test"  directory.
os.rmdir( "/tmp/test"  )

