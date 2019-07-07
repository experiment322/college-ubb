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
    a   dd -200
    b   dw 5
    fmt db "%d / %hd = %hd", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, [a]
        mov dx, [a + 2] ; dx:ax = a
        ;mov bx, [b]     ; bx = b
        idiv word [b]          ; ax = a / b
        cwde
        xor ebx, ebx
        mov ebx, [b]
        
        ;push word 0
        push eax         ; add ax on stack and convert to dword
        
        ;push word 0
        push dword [b]   ; add b on stack and convert to dword
        
        push dword [a]  ; add a on stack
        
        push fmt        ; add format string on stack
        
        call [printf]   ; print the result
        add  esp, 4 * 4 ; free the stack
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
