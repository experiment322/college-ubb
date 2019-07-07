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
    a dw 0x55
    b dw 0x15
    c dw 0xa6
    d dw 0x10
; our code starts here: (c + b + a) - (d + d)
segment code use32 class=code
    start:
        ; ...
        mov ax, [c]
        add ax, [b]
        add ax, [a] ; ax = (c + b + a)
        
        mov bx, [d]
        add bx, [d] ; bx = (d + d)
        
        sub ax, bx ; ax = (c + b + a) - (d + d)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
