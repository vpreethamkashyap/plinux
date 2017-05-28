#!/usr/bin/python

import sys
import time
import shutil
import os
import subprocess


var1 = 'Hello World!'
var2 = "Python Programming"

print "var1[0]: ", var1[0]
print "var2[1:5]: ", var2[1:5]


#!/usr/bin/python

# Updating Strings
#You can "update" an existing string by (re)assigning a variable to another string. 
#The new value can be related to its previous value or to a completely different string altogether. 
#For example −

var1 = 'Hello World!'

print "Updated String :- ", var1[:6] + 'Python'

print var1 + var2

print var1*2

print var1[1]
print var1[1:3]

#!/usr/bin/python
#String Formatting Operator
#One of Python's coolest features is the string format operator %. 
#This operator is unique to strings and makes up for the pack of having functions from C's printf() 
#family. Following is a simple example −

print "My name is %s and weight is %d kg!" % ('Zara', 21) 


# here we understand the list of inbuilt functions are defined in python library.

# Python String capitalize() Method
str = "this is string example....wow!!!";
print "str.capitalize() : ", str.capitalize()

#Python String center() Method
str = "this is string example....wow!!!";
print "str.center(40, 'a') : ", str.center(40, 'a')


#Python String count() Method
str = "this is string example....wow!!!";
sub = "i";
print "str.count(sub, 4, 40) : ", str.count(sub, 4, 40)
sub = "wow";
print "str.count(sub) : ", str.count(sub)

#Python String decode() Method
Str = "this is string example....wow!!!";
Str = Str.encode('base64','strict');
print "Encoded String: " + Str
print "Decoded String: " + Str.decode('base64','strict')

#Python String encode() Method
str = "this is string example....wow!!!";
print "Encoded String: " + str.encode('base64','strict')

#Python String endswith() Method
str = "this is string example....wow!!!";
suffix = "wow!!!";
print str.endswith(suffix)
print str.endswith(suffix,20)
suffix = "is";
print str.endswith(suffix, 2, 4)
print str.endswith(suffix, 2, 6)

#Python String expandtabs() Method
str = "this is\tstring example....wow!!!";
print "Original string: " + str
print "Defualt exapanded tab: " +  str.expandtabs()
print "Double exapanded tab: " +  str.expandtabs(16)

#Python String find() Method
str1 = "this is string example....wow!!!";
str2 = "exam";
print str1.find(str2)
print str1.find(str2, 10)
print str1.find(str2, 40)

#Python String index() Method
str1 = "this is string example....wow!!!";
str2 = "exam";
print str1.index(str2)
print str1.index(str2, 10)
print str1.index(str2, 40)

#Python String isalnum() Method
str = "this2009";  # No space in this string
print str.isalnum()
str = "this is string example....wow!!!";
print str.isalnum()

#Python String isalpha() Method
str = "this";  # No space & digit in this string
print str.isalpha()
str = "this is string example....wow!!!";
print str.isalpha()

#Python String isdigit() Method
str = "123456";  # Only digit in this string
print str.isdigit()
str = "this is string example....wow!!!";
print str.isdigit()

#Python String islower() Method
str = "THIS is string example....wow!!!"; 
print str.islower()
str = "this is string example....wow!!!";
print str.islower()

#Python String isnumeric() Method
str = u"this2009";  
print str.isnumeric()
str = u"23443434";
print str.isnumeric()

#Python String isspace() Method
str = "       "; 
print str.isspace()
str = "This is string example....wow!!!";
print str.isspace()

#Python String istitle() Method
str = "This Is String Example...Wow!!!";
print str.istitle()
str = "This is string example....wow!!!";
print str.istitle()

#Python String isupper() Method
str = "THIS IS STRING EXAMPLE....WOW!!!"; 
print str.isupper()
str = "THIS is string example....wow!!!";
print str.isupper()

#Python String join() Method
s = "-";
seq = ("a", "b", "c"); # This is sequence of strings.
print s.join( seq )

#Python String len() Method
str = "this is string example....wow!!!";
print "Length of the string: ", len(str)



#Python String ljust() Method
str = "this is string example....wow!!!";
print str.ljust(50, '0')

#Python String lower() Method
str = "THIS IS STRING EXAMPLE....WOW!!!";
print str.lower()

#Python String lstrip() Method
str = "     this is string example....wow!!!     ";
print str.lstrip()
str = "88888888this is string example....wow!!!8888888";
print str.lstrip('8')

#Python String maketrans() Methodfrom string import maketrans   # Required to call maketrans function.
intab = "aeiou"
outtab = "12345"
trantab = maketrans(intab, outtab)
str = "this is string example....wow!!!"
print str.translate(trantab)


#Python String max() Method
str = "this is really a string example....wow!!!";
print "Max character: " + max(str)
str = "this is a string example....wow!!!";
print "Max character: " + max(str)

#Python String min() Method
str = "this-is-real-string-example....wow!!!";
print "Min character: " + min(str)
str = "this-is-a-string-example....wow!!!";
print "Min character: " + min(str)

#Python String replace() Method
str = "this is string example....wow!!! this is really string";
print str.replace("is", "was")
print str.replace("is", "was", 3)

#Python String rfind() Method
str1 = "this is really a string example....wow!!!";
str2 = "is";
print str1.rfind(str2)
print str1.rfind(str2, 0, 10)
print str1.rfind(str2, 10, 0)
print str1.find(str2)
print str1.find(str2, 0, 10)
print str1.find(str2, 10, 0)

#Python String rindex() Method
str1 = "this is string example....wow!!!";
str2 = "is";
print str1.rindex(str2)
print str1.index(str2)

#Python String rjust() Method
str = "this is string example....wow!!!";
print str.rjust(50, '0')

#Python String rstrip() Method
str = "     this is string example....wow!!!     ";
print str.rstrip()
str = "88888888this is string example....wow!!!8888888";
print str.rstrip('8')

#Python String split() Method
str = "Line1-abcdef \nLine2-abc \nLine4-abcd";
print str.split( )
print str.split(' ', 1 )

#Python String splitlines() Method
str = "Line1-a b c d e f\nLine2- a b c\n\nLine4- a b c d";
print str.splitlines( )
print str.splitlines( 0 )
print str.splitlines( 3 )
print str.splitlines( 4 )
print str.splitlines( 5 )

#Python String startswith() Method
str = "this is string example....wow!!!";
print str.startswith( 'this' )
print str.startswith( 'is', 2, 4 )
print str.startswith( 'this', 2, 4 )

#Python String strip() Method
str = "0000000this is string example....wow!!!0000000";
print str.strip( '0' )

#Python String swapcase() Method
str = "this is string example....wow!!!";
print str.swapcase()
str = "THIS IS STRING EXAMPLE....WOW!!!";
print str.swapcase()

#Python String title() Method
str = "this is string example....wow!!!";
print str.title()

#Python String translate() Method
from string import maketrans   # Required to call maketrans function.

intab = "aeiou"
outtab = "12345"
trantab = maketrans(intab, outtab)
str = "this is string example....wow!!!";
print str.translate(trantab)

#Python String upper() Method
str = "this is string example....wow!!!";
print "str.capitalize() : ", str.upper()

#Python String zfill() Method
str = "this is string example....wow!!!";
print str.zfill(40)
print str.zfill(50)

#Python String isdecimal() Method
str = u"this2009";  
print str.isdecimal();
str = u"23443434";
print str.isdecimal();


