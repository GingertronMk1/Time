// This file is part of www.nand2tetris.org// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.

(MAIN)
    @SCREEN
    D=A
    @R1
    M=D         //Initialising  variable called R1, which will increment through the screen values

    @KBD
    D=M
    @WHITE
    D;JEQ
    @BLACK
    0;JMP

(BLACK)
    @R1
    A=M         //Accesses the memory address specified in R1
    M=-1        //Sets this value to -1
    @R1
    M=M+1       //Adds 1 to the value stored in R1
    D=M
    @24576      //Loads the value of 24576 into A
    D=D-A
    @MAIN
    D;JEQ       //Jumps to main if R1=24576
    @BLACK
    0;JMP


(WHITE)
    @R1
    A=M         //Accesses the memory address specified in R1
    M=0         //Sets this value to 0
    @R1
    M=M+1       //Adds 1 to the value stored in R1
    D=M
    @24576      //Loads the value of 24576 into A
    D=D-A
    @MAIN
    D;JEQ       //Jumps to main if R1=24576
    @WHITE
    0;JMP

