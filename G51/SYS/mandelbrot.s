; Program to print 'The Meadow Song'
; Username: psyje5
; Name: Jack Ellis
; Student ID: 4262333

; rows: R1
; cols: R2
; it:   R3
; r:    R4
; r2:   R5
; i:    R6
; i2:   R7
; tmp:  R8

    B main

xstart  DEFW    -400
xend    DEFW    400
ystart  DEFW    -265
yend    DEFW    265
ast     DEFB    "*",0
space   DEFB    " ",0
newl    DEFB    "\n",0

    ALIGN

main    ADR     R1,#53      ; R1 will do rows
        ADR     R2,#80      ; R2 will do columns
loop    SUB     R2,R2,#1
        LDR     R0,ast
        SWI     3
        CMP     R2,#0
        BEQ     newrow
        BNE     loop

newrow  SUB     R1,R1,#1
        ADD     R2,R2,80
        LDR     R0,newl
        SWI     3
        B       main
