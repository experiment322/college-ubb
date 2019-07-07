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

; our code starts here: (c + b) - a - (d + d)
segment code use32 class=code
    start:
        ; ...
        mov     ebx ,   0x0
        mov     bx  ,   [b]
        add     ebx ,   [c] ; ebx = c + b
        
        mov     eax ,   [d]
        mov     edx ,   [d + 4]
        add     eax ,   eax
        adc     edx ,   edx ; edx:eax = d + d
        
        mov     ecx ,   0x0
        mov     cl  ,   [a]
        sub     ebx ,   ecx ; ebx = (c + b) - a
        
        mov     ecx ,   0x0 ; ecx:ebx = (c + b) - a
        sub     ebx ,   eax
        sbb     ecx ,   edx ; ecx:ebx = (c + b) - a - (d + d)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
