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
    s dw -10, -9, -8, -7, -2, -1, 0, 0, 1, 2, 3, 2, 1, 10, 20, 30, 40, 50
    len_s equ ($ - s) / 2
    lbgn dd s
    lend dd s + 2
    format db "%d ", 0

; our code starts here
segment code use32 class=code
    start:
        mov ecx, len_s - 1
        jecxz final ; if there was only one element in s skip
        cld
        mov esi, s ; in esi store the last element in the current increasing sequence
        mov edi, s + 2 ; in edi store the next element
        mov edx, [lbgn] ; in edx store the start address of the computed sequence
        search:
            cmpsw
            jge reset ; if we found a smaller number reset the current sequence
        loop search
        reset:
            mov eax, [lend]
            sub eax, [lbgn] ; store in eax the length of the old sequence in bytes
            mov ebx, esi
            sub ebx, edx ; store in ebx the length of the actual sequence in bytes
            cmp eax, ebx
            jge do_not_update_sequence ; if the old sequence is longer or equal with the current one do not replace it
            mov [lbgn], edx
            mov [lend], esi
            do_not_update_sequence:
            mov edx, esi ; reset the start of the current sequence
            cmp ecx, 0
            jnz search ; search again from where we left if we didn't reach the end of the list
        final:
        
        ; printing
        cld
        mov esi, [lbgn]
        mov ecx, [lend]
        sub ecx, [lbgn]
        shr ecx, 1
        print:
            lodsw
            cwde
            push ecx
            push eax
            push format
            call [printf]
            add esp, 4 * 2
            pop ecx
        loop print
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
