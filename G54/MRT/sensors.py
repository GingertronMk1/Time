import grovepi
import grove6axis
import time

grove6axis.init6Axis() # Initialise the accelerometer

constant = 0.05 # The constant to be used in in the low-pass filter
t = 0           # Initialise time
adiffLo = 0     # Initialise the low-passed value for the difference in light levels
leanLo = 0      # Initialise the low-passed value for the lean

while True:
  if False:
    # Read from an analog sensor on input 0
    a0 = grovepi.analogRead(0)

    # Read from an analog sensor on input 1
    a1 = grovepi.analogRead(1)

    # Calculate the absolute difference between a0 and a1
    adiff = abs(a0-a1)

    # Apply a low-pass filter to this difference
    adiffLo = adiffLo*(1.0-constant) + adiff * constant

    # Output the data
    if adiffLo > 200:     # If the difference is more than 200
        t += 1              # Increase the time by 1
        if t > 200:         # If that time is more than 200 (should be ~20s)
            print("For your eye health please look away from the screen now") # Have a go at the user
        else:               #Otherwise print the value
            print("Big difference!   Specifically: %4.0f"%(adiffLo), "\ta0: ", a0, " a1:",a1, " t: ", t)
    else:           # If the difference is small
        t = 0       # Reset the timer, print the values
        print("Small difference! Specifically: %4.0f"%(adiffLo), "\ta0: ", a0, " a1:",a1, " t: ", t)
  else:
    # Read the first value of the 3-tuple returned by getOrientation()
    lean = grove6axis.getOrientation()[0]
    # Apply a low-pass filter to this
    leanLo = leanLo * (1.0-constant) + lean * constant
    # Print it
    print(leanLo)




    # Read roughly 10 times a second
    # - n.b. analog read takes time to do also
    time.sleep(0.1)
