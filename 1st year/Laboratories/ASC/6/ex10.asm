bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern printf
import printf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s db 1, 2, 3, 4, 4, 5, 6, 1, 2, 8, 8, 8, 100
    len_s equ $-s
    d resb len_s
    len_d dd 0
    fmt db "%i ", 0
    newl db 10, 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, len_s ; set ecx to the length of s
        jecxz final ; jump to final if s is empty
        for_s:
            push ecx ; save s index on stack
            mov dl, [s + ecx - 1] ; set dl to the current value from s
            mov ecx, [len_d] ; set ecx to the current length of d for the second for loop
            jecxz add_to_d ; skip the loop if d is empty and add s[i] to d
            for_d:
                cmp dl, [d + ecx - 1] ; compare the current value from s to the one from d
                je dont_add_to_d ; if they are equal do not add it again to d
            loop for_d
            add_to_d:
                mov ecx, [len_d] ; reset ecx to d's length
                mov [d + ecx], dl ; add s[i] to d
                inc dword [len_d] ; increase d length
            dont_add_to_d:
            pop ecx ; restore s index from stack
        loop for_s
        final:
        ; printing s for debugging
        mov ecx, len_s
        jecxz after_print_s
        print_s:
            push ecx
            movzx eax, byte [s + ecx - 1]
            push eax
            push fmt
            call [printf]
            add esp, 4 * 2
            pop ecx
        loop print_s
        after_print_s:
        ; print new line
        push newl
        call [printf]
        add esp, 4
        ; printig d for debugging
        mov ecx, [len_d]
        jecxz after_print_d
        print_d:
            push ecx
            movzx eax, byte [d + ecx - 1]
            push eax
            push fmt
            call [printf]
            add esp, 4 * 2
            pop ecx
        loop print_d
        after_print_d:
        ; print new line
        push newl
        call [printf]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
