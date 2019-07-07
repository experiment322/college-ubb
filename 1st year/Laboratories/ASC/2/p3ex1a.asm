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
    a db 0x99
    b db 0x36
    c db 0x1f
    d dw 0x1000
; our code starts here: ((a + b - c) * 2 + d - 5) * d
segment code use32 class=code
    start:
        ; ...
        mov al, [a]
        add al, [b]
        sub al, [c] ; al = (a + b - c)
        
        mov bl, 0x2 ; bl = 2
        mul bl ; ax = (a + b - c) * 2
        add ax, [d] ; ax = (a + b - c) * 2 + d
        sub ax, 0x5 ; ax = (a + b - c) * 2 + d - 5
        
        mul word [d] ; dx:ax = ((a + b - c) * 2 + d - 5) * d
        push dx
        push ax
        pop eax ; eax = ((a + b - c) * 2 + d - 5) * d
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
