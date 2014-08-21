#!/usr/bin/python
import os,sys
os.system("/usr/bin/raspistill -t 30000 -tl 1000 -q 30 -vf -w 128 -h 128 -o /var/www/page/test.jpg")
print "Location: http://192.168.1.13\n"
