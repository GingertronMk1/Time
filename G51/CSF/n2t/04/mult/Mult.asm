    @0
    D=A
    @R2
    M=D     //Initialising all registers to 0
(LOOP)
    @R1
    D=M
    @END
    D;JEQ   //Checks if R1 is equal to zero; if it is, go to end loop

    @R0
    D=M     //Sets register D equal to R0
    @R2
    M=D+M   //Adds D (R0) to R2

    @R1
    M=M-1   //Subtracts 1 from R1
    @LOOP
    0;JMP   //Loops back to the beginning
(END)
    @END
    0;JMP
