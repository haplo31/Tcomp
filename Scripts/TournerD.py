#!/usr/bin/python
import cgi,serial
print "Location: http://192.168.1.13\n"
form=cgi.FieldStorage()
tourner="D"
ser=serial.Serial('/dev/ttyACM0',115200)
ser.write(tourner)




