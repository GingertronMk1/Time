module MyTAMCode where

import TAMCode
import TAMInterpreter

taskA = [GETINT,        -- take an INT from stdin, push to stack top
         LOADL 1,       -- push onto the stack 1
         Label "comp",  -- label
         LOAD (SB 0),   -- push contents of stack bottom to top
         LOAD (SB 1),   -- push contents of stack bottom + 1 to top
         LSS,           -- if 
         JUMPIFNZ "end",
         LOAD (SB 1),
         PUTINT,
         LOADL 1,
         ADD,
         JUMP "comp",
         Label "end",
         HALT]

taskB = [GETINT,        -- take int from stdin push to stack
         CALL "fac",    -- call "fac"
         PUTINT,        -- put the result
         HALT,          -- stop
         Label "fac",   -- "fac"ing hell
         LOADL 1,       -- push 1 to stack
         LOAD (LB (-1)),-- load local base -1 (i.e. value at top of stack on call of fac)
         LSS,           -- if it's less than 1
         JUMPIFZ "one", -- jump to the bit that deals with that, otherwise...
         LOAD (LB (-1)),-- load the value fac was called with again
         LOAD (LB (-1)),-- and again...
         LOADL 1,       -- push 1 to the stack
         SUB,           -- subtract it from the second value
         CALL "fac",    -- call "fac" on that
         MUL,           -- multiplying
         JUMP "ret",    -- when we're done, return
         Label "one",   -- if it was one (remember that?)
         LOADL 1,       -- push one to the stack
         Label "ret",
         RETURN 1 1]    -- return, with the new top of stack being the top of the stack from the subroutine
