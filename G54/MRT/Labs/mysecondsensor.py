import grovepi
import time

# output a CSV header to the file
print ("time,digital,analog")
while True:
    # read from a digital sensor on input 4
    d=grovepi.digitalRead(4)
    # read from an analog sensor on input 0
    a= grovepi.analogRead(0)
    # get a timestamp so we know when it happened
    timestamp = time.time()
    # output all sensor values as comma separated values print ("%f,%d,%d"%(timestamp,d,a))
    # Read roughly 10 times a second
    # - n.b. analog read takes time to do also
    time.sleep(0.1)
