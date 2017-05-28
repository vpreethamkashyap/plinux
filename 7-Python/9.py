#!/usr/bin/python

import sys
import time
import shutil
import os
import subprocess

#Accessing Values in Dictionary:
dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}
print "dict['Name']: ", dict['Name']
print "dict['Age']: ", dict['Age']

dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}
print "dict['Alice']: ", dict['Alice']


#Updating Dictionary
dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}
dict['Age'] = 8; # update existing entry
dict['School'] = "DPS School"; # Add new entry
print "dict['Age']: ", dict['Age']
print "dict['School']: ", dict['School']

#Delete Dictionary Elements
dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}
del dict['Name']; # remove entry with key 'Name'
dict.clear();     # remove all entries in dict
del dict ;        # delete entire dictionary
print "dict['Age']: ", dict['Age']
print "dict['School']: ", dict['School']


#Properties of Dictionary Keys
dict = {'Name': 'Zara', 'Age': 7, 'Name': 'Manni'}
print "dict['Name']: ", dict['Name']

dict = {['Name']: 'Zara', 'Age': 7}
print "dict['Name']: ", dict['Name']

#SN	Function with Description

#cmp(dict1, dict2)
#Compares elements of both dict.
#Python dictionary cmp() Method
dict1 = {'Name': 'Zara', 'Age': 7};
dict2 = {'Name': 'Mahnaz', 'Age': 27};
dict3 = {'Name': 'Abid', 'Age': 27};
dict4 = {'Name': 'Zara', 'Age': 7};
print "Return Value : %d" %  cmp (dict1, dict2)
print "Return Value : %d" %  cmp (dict2, dict3)
print "Return Value : %d" %  cmp (dict1, dict4)
	
#len(dict)
#Gives the total length of the dictionary. This would be equal to the number of items in the dictionary.
#Python dictionary len() Method
dict = {'Name': 'Zara', 'Age': 7};
print "Length : %d" % len (dict)
	
#str(dict)
#Produces a printable string representation of a dictionary
#Python dictionary str() Method
dict = {'Name': 'Zara', 'Age': 7};
print "Equivalent String : %s" % str (dict)

#type(variable)
#Returns the type of the passed variable. If passed variable is dictionary, then it would return a dictionary type.
#Python dictionary type() Method
dict = {'Name': 'Zara', 'Age': 7};
print "Variable Type : %s" %  type (dict)
