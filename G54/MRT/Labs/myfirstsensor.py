import grovepi
import time

while True:
    #read from a digital sensor on input 4
    d= grovepi.digitalRead(4)
    #read from an analog sensor on input 0
    a= grovepi.analogRead(0)
    # output the data
    print ("D:",d)
    print ("A:",a)
    # Read roughly 10 times a second
    # - n.b. analog read takes time to do also
    time.sleep(0.1)
