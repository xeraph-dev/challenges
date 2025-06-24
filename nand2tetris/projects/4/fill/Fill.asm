// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed,
// the screen should be cleared.

(RESET_STATE)
    @8192 // Entire SCREEN in memory = KBD - SCREEN
    D=A
    @screenMemorySize
    M=D
    @screenIndex
    M=D

(LOOP)
    @screenIndex
    M=M-1
    D=M

    @SCREEN
    D=D+A
    @currentScreenIndex
    M=D

    @KBD
    D=M
    @BLACK
    D;JNE

    (WHITE)
        @currentScreenIndex
        A=M
        M=0

        @END_DRAWING
        0;JMP

    (BLACK)
        @currentScreenIndex
        A=M
        M=-1

    (END_DRAWING)

    @screenIndex
    D=M
    @RESET_STATE
    D;JEQ

    @LOOP
    0;JMP
