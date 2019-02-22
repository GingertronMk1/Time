import grovepi
import time

while True:
    #read from an analog sensor on input 0
    a0= grovepi.analogRead(0)
    #read from an analog sensor on input 1
    a1= grovepi.analogRead(1)
    # output the data
    print ("0:",a0)
    print ("1:",a1)
    # Read roughly 10 times a second
    # - n.b. analog read takes time to do also
    time.sleep(0.1)
