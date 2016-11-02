# Coursework 1
##### By Jack Ellis
#### 806 Words
## TileMap/TileMap.java

There were 19 lines of white space after the end of the code in the file.
This is a problem as despite the space essentially being empty, it still has memory implications, and so will slow
load times on slower systems
The solution is simply to delete the 19 blank lines. This works because there are not functions being declared or
called, or indeed anything at all happening, so unless the programming language calls for it, there's not use to it
being there, and no harm to be done in removing it.
I removed it, and the program continued to work as before.
![](Fig 1a.png)
![](Fig 1b.png)

There was a comment on a piece of code that was entirely useless. On a function called replace(), the comment said
"replace something". This was obvious from the function name, but the comment added no detail as to what was
replaced, or to what effect. Looking further into the code I found that the function was called once, with
hard-coded variables input.
Deleting this calling had no effect on the game, so the whole thing could be deleted.
Before I deleted it, I looked more thoroughly at the function and determined that it replaced the value held within
one tile on the map with another value specified in the arguments of the function. I replaced the comment with
something more useful to another developer, then deleted the whole function as it was just wasting memory at that
point.
![](Fig 2a.png)
![](Fig 2b.png)

There was a seven-line block of code that was entirely commented out, despite being seemingly identical to the code
above, bar two lines being switched around.
Again, this is a waste of space, but it's also confusing to a developer new to the code.
I commented out the code above, and un-commented the offending paragraph, only to find that the game then ran very
poorly, with frames not being redrawn correctly.
I re-un-commented the 'good' block, and deleted the bad one.
[Fig 3a,3b,3c]
![](Fig 3a.png)
![](Fig 3b.png)
![](Fig 3c.png)

## Manager/Keys.java

There was an if... else if... statement with 8 cases, all of which checked the same single variable and acted
according to what value it held.
This is confusing to read, and seems excessive given that we're checking one variable that can hold one of 8 values.
The solution here is to replace the if... else if... block with a switch statement that does the exact same job.
This is better as it is easier to read for another developer, as well as being more easily extensible
[Fig 4a,4b]
![](Fig 4a.png)
![](Fig 4b.png)

Also in this section, the variables were not named very clearly; they were labeled as K1-8.
This is an issue of readability, as it was not clear what they corresponded to.
I replaced the names with the names of the buttons they represented here and in every other file they were used in.
This is good as it adds clarity

Finally (in this function), the function is declared as an int, so it has to return something. But it's hard-coded
to return 0.
This takes more processing time, as you've then to wait while the function returns 0 inevitably, then you can get on
with the rest of the program.
I replaced the 'int' in the declaration with 'void', and removed the 'return 0'
This is better as it makes the program shorter and more manageable, and has no negative side effects on the
performance of the game

## Entity/Player.java

Here there was an identical block of code repeated four times, one for each direction the player could face
This is a waste of memory space, as well as making the code longer and harder to read.
The solution is to create a function out of the block of code, and replace each instance of the block with the
function.
This is better as it makes the code shorter, and if the function (which checks if the player is on water) needs
extending in the future, this makes the process far easier, as you do not then need to repeat the same change four
times.
![](Fig 5a.png)
![](Fig 5b.png)

## Class Diagram

![](CW1 Class Diagram.png)

First I looked at the Main package. ``GamePanel`` is a part of ``Game``, and everything else is a part of ``GamePanel``, so
``GamePanel`` is an aggregation of game; it cannot function without game. GameStateManager is then an aggregation of
GamePanel, as it cannot function without it and imports/uses parts of ``GamePanel``. ``GameState`` and ``GameStateManager`` have a
bidirectional relationship, as ``GameStateManager`` takes parts and functions from ``GameState``, and vice-versa.

Everything else in the package ``GameState`` inherits ``GameState``, so they're all inheritance relationships.

In ``Manager``, ``GameStateManager`` depends on ``JukeBox`` (it initializes it, and uses its functions, but ``JukeBox`` doesn't do
        anything with ``GameStateManager``). Data is used only in ``PlayState`` and ``GameOverState``, so these are bidirectional relationships.

``Content`` is only referenced in ``GameOverState``, ``PauseState``, and ``MenuState``; they aggregate it with other things from other classes.
Hence, aggregation relationships.
