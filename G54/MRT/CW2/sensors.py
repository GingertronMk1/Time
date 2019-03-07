import grovepi
import grove6axis
import time
import math

# The accelerometer should be plugged into an I2C port
# It should be a version 2.0 - the more complicated looking one
grove6axis.init6Axis() # Initialise the accelerometer

constant = 0.05       # The constant to be used in in the low-pass filter
t = 0                 # Initialise time
aDiffLo = 0           # Initialise the low-passed value for the difference in light levels
leanLo = math.pi/2 # Initialise the low-passed value for the lean

problemTime = 180 # The number of seconds before there's a problem
problemAngle = math.pi/10

def loPass(curr, val):
    const = 0.05
    return val * (1.0 - constant) + curr * constant

while True:
    # Read from an analog sensor on input 0
    a0 = grovepi.analogRead(0)

    # Read from an analog sensor on input 1
    a1 = grovepi.analogRead(1)

    # Calculate the absolute difference between a0 and a1
    aDiff = abs(a0-a1)

    # Apply a low-pass filter to this difference
    aDiffLo = loPass(aDiff, aDiffLo)

    # Read the first value of the 3-tuple returned by getOrientation()
    # This value will be in radians, with flat on its back being 0
    # pi/3 should be considered a problem angle
    # The 3-axis sensor should be positioned with the cable port on the bottom
    lean = grove6axis.getOrientation()[2]

    # Apply a low-pass filter to this
    leanLo = loPass(lean, leanLo)
 
    # Output the data
    if aDiffLo > 200:     # If the difference is more than 200
        t += 1            # Increase the time by 1
        if t > problemTime * 10:      # If that time is more than 200 (should be ~20s)
            print("For your eye health please look away from the screen now") # Have a go at the user
        else:               #Otherwise print the value
            if leanLo > (math.pi/2 - problemAngle):
                print("Leaning fine")
            else:
                print("Leaning too much!")
            print("raw: ", lean, "\tlowPassed: ", leanLo)
            print("Big difference!   Specifically: %4.0f"%(aDiffLo), "\ta0: ", a0, " a1:",a1, " t: ", t)
    else:           # If the difference is small
        t = 0       # Reset the timer, print the values
        print("Small difference! Specifically: %4.0f"%(aDiffLo), "\ta0: ", a0, " a1:",a1, " t: ", t)

    # Read roughly 10 times a second
    # - n.b. analog read takes time to do also
    time.sleep(0.1)
