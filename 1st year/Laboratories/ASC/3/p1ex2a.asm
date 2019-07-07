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
    a db 0xff
    b dw 0x04ff
    c dd 0xffff00ff
    d dq 0xfffffff10000f602

; our code starts here: (b + b) + (c - a) + d
segment code use32 class=code
    start:
        ; ...
        mov     edx ,   0x0
        mov     dx  ,   [b] ; dx = b
        add     dx  ,   [b] ; dx = (b + b)
        
        mov     eax ,   0x0
        mov     al  ,   [a] ; eax = a
        sub     [c] ,   eax
        mov     eax ,   [c] ; eax = (c - a)
        
        add     eax ,   edx ; eax = (b + b) + (c - a)
        
        mov     edx ,   0x0
        add     eax ,   [d]
        adc     edx ,   [d + 4] ; edx:eax = (b + b) + (c - a) + d
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
