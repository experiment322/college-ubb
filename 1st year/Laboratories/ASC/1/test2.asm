bits 32

extern exit
import exit msvcrt.dll

global start

segment data use32 class=data
    ; ...
    a db 0

segment code use32 class=code
    start:
        ; ...
        mov eax, a
        lea eax, [a]
        lea eax, [fs:0]
        mov ax, cs
        mov ax, ds
        mov ax, ss
        ; exit(0)
        push    dword 0
        call    [exit]
