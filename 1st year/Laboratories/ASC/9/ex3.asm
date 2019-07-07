bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern fopen, fread, fclose, printf
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    frmt db "%i", 10, 0
    mode db "rb", 0
    file db "ex3.txt", 0
    fdes dd 0
    freq times 10 dd 0
    buff times 64 db 0
    blen equ $ - buff

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
        
        readfile:
            push dword [fdes]
            push dword blen
            push dword 1
            push dword buff
            call [fread]
            add esp, 4 * 4
            
            cmp eax, 0
            je stopreading
            
            mov ecx, eax
            mov esi, buff
            cld
            count:
                lodsb
                cmp al, "0"
                jb skip
                cmp al, "9"
                ja skip
                movzx eax, al
                inc dword [freq + eax * 4 - "0" * 4]
            skip:
            loop count
            
        jmp readfile
        stopreading:
        
        mov ecx, 0
        add ecx, [freq + 4 * 0]
        add ecx, [freq + 4 * 2]
        add ecx, [freq + 4 * 4]
        add ecx, [freq + 4 * 6]
        add ecx, [freq + 4 * 8]
        
        push dword ecx
        push dword frmt
        call [printf]
        add esp, 4 * 2

        push dword [fdes]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
