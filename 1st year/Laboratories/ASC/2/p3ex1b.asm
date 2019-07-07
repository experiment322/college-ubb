bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 0x50
    b db 0xaf
    c db 0x19
    d db 0x46
; our code starts here: (a + b) - (c + d)
segment code use32 class=code
    start:
        ; ...
        mov al, [a]
        add al, [b] ; al = a + b
        
        mov bl, [c]
        add bl, [d] ; bl = c + d
        
        sub al, bl ; al = (a + b) - (c + d)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
