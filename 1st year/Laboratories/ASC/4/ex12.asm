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
    a dw 0b1010_1101_1100_0101
    b dw 0b0011_1001_1010_1100

; our code starts here
segment code use32 class=code
    start:
        ; ...
        xor ecx, ecx        ; zero ecx
        
        xor eax, eax        ; zero eax
        mov ax , [a]
        and eax, 0b0000_0000_0000_0000_0000_0000_0000_0111 ; keep bits 0-2 of a
        shl eax, 0x7        ; move the bits 7 places to left
        or  ecx, eax        ; ecx[7-9] = a[0-2]
        
        xor eax, eax        ; zero eax
        mov ax , [b]
        and eax, 0b0000_0000_0000_0000_0011_1111_0000_0000 ; keep bits 8-13 of b
        shl eax, 0x2        ; move the bits 2 places to left
        or  ecx, eax        ; ecx[10-15] = a[8-13]
        
        or  ecx, 0b1111_1111_1111_1111_0000_0000_0000_0000 ; fill ecx[16-31] with 1s
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
