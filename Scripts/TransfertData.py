#!/usr/bin/python
import cgi,serial,time
print "Location: http://192.168.1.13\n"
form=cgi.FieldStorage()
actionman=form.getvalue('action')
ser=serial.Serial("/dev/ttyACM0",115200)
time.sleep(1)
ser.setDTR(level=0)
time.sleep(1)
ser.write(actionman)
initrec=0
while initrec==0 :
	valrec= ser.readline()
	if valrec=="done\r\n" :
		initrec=1

