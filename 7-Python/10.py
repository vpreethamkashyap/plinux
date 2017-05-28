#!/usr/bin/python

import sys
import time
import shutil
import os
import subprocess


#Python Date & Time
ticks = time.time()
print "Number of ticks since 12:00am, January 1, 1970:", ticks

localtime = time.localtime(time.time())
print "Local current time :", localtime


localtime = time.asctime( time.localtime(time.time()) )
print "Local current time :", localtime


cal = calendar.month(2008, 1)
print "Here is the calendar:"
print cal

#Python time altzone() Method
print "time.altzone %d " % time.altzone

#Python time asctime() Method
t = time.localtime()
print "time.asctime(t): %s " % time.asctime(t)

#Python time clock() Method
def procedure():
    time.sleep(2.5)

# measure process time
t0 = time.clock()
procedure()
print time.clock() - t0, "seconds process time"

# measure wall time
t0 = time.time()
procedure()
print time.time() - t0, "seconds wall time"


#Python time ctime() Method
print "time.ctime() : %s" % time.ctime()

#Python time gmtime() Method
print "time.gmtime() : %s" % time.gmtime()

#Python time localtime() Method
print "time.localtime() : %s" % time.localtime()

#Python time mktime() Method
t = (2009, 2, 17, 17, 3, 38, 1, 48, 0)
secs = time.mktime( t )
print "time.mktime(t) : %f" %  secs
print "asctime(localtime(secs)): %s" % time.asctime(time.localtime(secs))

#Python time sleep() Method
print "Start : %s" % time.ctime()
time.sleep( 5 )
print "End : %s" % time.ctime()

#Python time strftime() Method
t = (2009, 2, 17, 17, 3, 38, 1, 48, 0)
t = time.mktime(t)
print time.strftime("%b %d %Y %H:%M:%S", time.gmtime(t))

#Python time strptime() Method
struct_time = time.strptime("30 Nov 00", "%d %b %y")
print "returned tuple: %s " % struct_time

#Python time time() Method
print "time.time(): %f " %  time.time()
print time.localtime( time.time() )
print time.asctime( time.localtime(time.time()) )

#Python time tzset() Method
os.environ['TZ'] = 'EST+05EDT,M4.1.0,M10.5.0'
time.tzset()
print time.strftime('%X %x %Z')
os.environ['TZ'] = 'AEST-10AEDT-11,M10.5.0,M3.5.0'
time.tzset()
print time.strftime('%X %x %Z')




























