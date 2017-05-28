#!/usr/bin/python

import sys
import time
import shutil
import os
import subprocess


# A module allows you to logically organize your Python code.



# Import module support
import support

# Now you can call defined function that module as follows
support.print_func("Zara")


########################################################################
Money = 2000
def AddMoney():
   # Uncomment the following line to fix the code:
   # global Money
   Money = Money + 1

print Money
AddMoney()
print Money


########################################################################
#The dir( ) Function
# Import built-in module math
import math

content = dir(math)

print content

