import grovepi
import grove6axis
import time
import math

# The accelerometer should be plugged into an I2C port
# It should be a version 2.0 - the more complicated looking one
grove6axis.init6Axis() # Initialise the accelerometer

t = 0                 # Initialise time
aDiffLo = 0           # Initialise the low-passed value for the difference in light levels
leanLo = math.pi/2    # Initialise the low-passed value for the lean

problemTime = 20         # The number of seconds before there's a problem
problemAngle = math.pi/8 # The angle at which there is a problem

calibrationPassesInit = 100 # Number of calibration passes
calibrationPasses = calibrationPassesInit # Calibration pass counter

a0Cal = 0 # Accumulator for the values recorded by a0
a1Cal = 0 # Accumulator for the values recorded by a1

def loPass(curr, val):
  const = 0.05
  return val * (1.0 - const) + curr * const

while True:
  # Read from an analog sensor on input 0 (this should be the top one)
  a0 = grovepi.analogRead(0)


  # Read from an analog sensor on input 1 (this should be the bottom one)
  a1 = grovepi.analogRead(1)

  if calibrationPasses > 0:
    a0Cal += a0 #/ calibrationPassesInit
    a1Cal += a1 #/ calibrationPassesInit
    print("Calibrating, ", calibrationPasses, "a0Cal: ", a0Cal, " a1Cal: ", a1Cal)
    calibrationPasses -= 1
  elif calibrationPasses == 0:
    a0Cal = a0Cal / calibrationPassesInit
    a1Cal = a1Cal / calibrationPassesInit
    print("Calibrating done, a0Cal: ", a0Cal, " a1Cal: ", a1Cal)
    calibrationPasses -= 1
  else:
    a0Fix = a0 - a0Cal
    a1Fix = a1 - a1Cal

    # Calculate the absolute difference between a0 and a1
    aDiff = a1Fix / a0Fix

    # Apply a low-pass filter to this difference
    aDiffLo = loPass(aDiff, aDiffLo)

    # Read the first value of the 3-tuple returned by getOrientation()
    # This value will be in radians, with flat on its back being 0
    # The 3-axis sensor should be positioned with the cable port on the bottom
    # Due to prototyping constraints the yaw value is used
    lean = grove6axis.getOrientation()[1]

    # Apply a low-pass filter to this
    leanLo = loPass(lean, leanLo)

    # Output the data
    if aDiffLo > 1.2:     # If the difference is more than 200
      t += 0.1            # Increase the time by 0.1
      if t > problemTime: # If that time is more than 200 (should be ~20s)
        print("You have been looking at the screen for too long, please look away now")
      else:               # Else we have a look at how much the user's leaning
        if abs(leanLo) < problemAngle:  # If the LP'd lean value is within bounds...
          print("You are looking at a screen, and leaning fine")
        else:                           # Otherwise...
          print("You are looking at a screen, and leaning too much!")
    else:         # If the difference is small
      t = 0       # Reset the timer, print the values
      print("You are not looking at a screen")

    # Read roughly 10 times a second
    # - n.b. analog read takes time to do also
  time.sleep(0.1)
