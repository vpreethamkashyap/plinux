#!/usr/bin/python3
import sys
import time
import shutil
import os
import subprocess

print ("\nThis Python script help you to understand Types of Operator \r\n")


print ("Python language supports the following types of operators. \r\n")
print ("Arithmetic Operators \r\n")
print ("Comparison (Relational) Operators \r\n")
print ("Assignment Operators \r\n")
print ("Logical Operators \r\n")
print ("Bitwise Operators \r\n")
print ("Membership Operators \r\n")
print ("Identity Operators \r\n")
print ("Let us have a look on all operators one by one. \r\n")


raw_input("Press enter to see how to aithrmetic operations occurs\n")

var a = 50
var b = 20
var c

c = a+b
print("Addition of a & b is %d \r\n" %c)
c = a-b
print("Subtraction of a & b is %d \r\n" %c)
c = a*b
print("Multiplication of a & b is %d \r\n"%c)
c = a/b
print("Division of a & b is %d \r\n"%c)
c = a%b
print("Modulus of a & b is %d \r\n" %c)
c = a**b
print("Exponent of a & b is %d \r\n" %c)
c = a//b
print("Floor Division of a & b is %d \r\n" %c)


raw_input("Press enter to see how to aithrmetic operations occurs\n")
print("Python Comparison Operators\r\n")
if(a == b):
	print(" a & b are same \r\n")

if(a != b):
	print("a & b are not same\r\n")

if(a > b):
	print("a is greater than b\r\n")

if(a < b):
	print("b is greater than a\r\n")

raw_input("Press enter to see how to Bitwise operations occurs\n")

print ("\r\n Bit wise operator a&b %b \r\n" % (a&b))
print ("\r\n Bit wise operator a|b %b \r\n" % (a|b))
print ("\r\n Bit wise operator a^b %b \r\n" % (a^b))
print ("\r\n Bit wise operator ~a  %b \r\n" % (~a))



