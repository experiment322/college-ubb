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
    a db 0xf0
    c db 0x04
    b dw 0xf0f0
    d dd 0x1000f602
    x dq 0xfffffff10000f602

; our code starts here: (a * b + 2) / (a + 7 - c) + d + x
segment code use32 class=code
    start:
        ; ...
        mov     eax ,   0x0
        mov     al  ,   [a] ; ax = a
        mul     word [b]    ; dx:ax = a * b
        
        add     ax  ,   0x2
        adc     dx  ,   0x0 ; dx:ax = a * b + 2
        
        mov     ebx ,   0x0
        mov     bl  ,   [a]
        add     bl  ,   0x7 ; bl = a + 7
        sub     bl  ,   [c] ; bl = a + 7 - c
        
        div     bx          ; ax = (a * b + 2) / (a + 7 - c)
        
        add     eax ,   [d] ; eax = (a * b + 2) / (a + 7 - c) + d
        
        add     [x]     ,   eax
        adc     [x + 4] ,   word 0x0   ; x = (a * b + 2) / (a + 7 - c) + d + x
        
        mov     eax ,   [x]
        mov     edx ,   [x + 4]     ; edx:eax = (a * b + 2) / (a + 7 - c) + d + x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
