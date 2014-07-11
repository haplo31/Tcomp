!/usr/bin/python
import cgi,serial
print "Location: http://192.168.1.13\n"
form=cgi.FieldStorage()
action=form.getvalue('action')
ser=serial.Serial('/dev/ttyACM0',115200)
ser.write(action)
initrec=0
while initrec==0 :
	valrec= ser.readline()
	if valrec=="done" :
		initrec=1