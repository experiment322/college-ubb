bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern scanf, fopen, fclose, fprintf
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    fmtr db "%i", 0
    fmtw db "%i", 10, 0
    mode db "w", 0
    file db "ex12.txt", 0
    fdes dd 0
    nmbr dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mode
        push dword file
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je final
        mov [fdes], eax
        
        readwrite:
            push dword nmbr
            push dword fmtr
            call [scanf]
            add esp, 4 * 2
            
            cmp dword [nmbr], 0
            je stopreadwrite
            
            push dword [nmbr]
            push dword fmtw
            push dword [fdes]
            call [fprintf]
            add esp, 4 * 3
        jmp readwrite
            
        stopreadwrite:
        push dword [fdes]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
