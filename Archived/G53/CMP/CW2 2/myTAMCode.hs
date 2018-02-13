module MyTAMCode where

import TAMCode
import TAMInterpreter

taskA = [GETINT,
         LOADL 1,
         Label "comp",
         LOAD (SB 0),
         LOAD (SB 1),
         LSS,
         JUMPIFNZ "end",
         LOAD (SB 1),
         PUTINT,
         LOADL 1,
         ADD,
         JUMP "comp",
         Label "end",
         HALT]

taskB = [GETINT,
         CALL "fac",
         PUTINT,
         HALT,
         Label "fac",
         LOADL 1,
         LOAD (LB (-1)),
         LSS,
         JUMPIFZ "one",
         LOAD (LB (-1)),
         LOAD (LB (-1)),
         LOADL 1,
         SUB,
         CALL "fac",
         MUL,
         JUMP "ret",
         Label "one",
         LOADL 1,
         Label "ret",
         RETURN 1 1]
