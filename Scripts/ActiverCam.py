#!/usr/bin/python
import os,sys
os.system("/usr/bin/raspistill -o /var/www/page/test.jpg -tl 1000 -t 3600000 -w 256 -h 256")
print "Location: http://192.168.1.13\n"
