bits 32

extern exit, printf, concat
import exit msvcrt.dll
import printf msvcrt.dll

global start

segment data use32 class=data
    a db "-first string-", 0
    b db "-second string-", 0
    tmp times $ - a db 0
    fmt db "%s", 13, 10, 0

segment code use32 class=code
    start:
        ; ...
        push a
        push tmp
        call concat
        add esp, 4 * 2
        
        push b
        push tmp
        call concat
        add esp, 4 * 2
        
        push tmp
        push fmt
        call [printf]
        add esp, 4 * 2
        
        mov byte [tmp], 0 ; reset tmp to an empty string
        
        push b
        push tmp
        call concat
        add esp, 4 * 2
        
        push a
        push tmp
        call concat
        add esp, 4 * 2
        
        push tmp
        push fmt
        call [printf]
        add esp, 4 * 2
        
        ; exit(0)
        push    dword 0
        call    [exit]
