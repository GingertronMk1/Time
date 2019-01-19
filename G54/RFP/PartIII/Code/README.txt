BrickBreaker in Haskell
=======================

This is a Breakout clone made using the Haskell functional programming language, with help from the Threepenny GUI suite.

It consists of a single file containing all of the required functions, which were by and large written from scratch, with some of the code in the `setup` function being adapted from the lecture which introduced us to the Threepenny GUI library.

It is a simple clone: the game is endless, with the ball getting faster and faster as the levels progress until the player dies.
The objective of the game is to use the paddle to prevent the ball hitting the bottom of the screen while breaking the bricks arranged in rows at the top.
Each brick broken adds to the player's score, and breaking all of the bricks advances the player to the next level, where the bricks are worth more and the ball moves faster.
