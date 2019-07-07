bits 32

extern exit, scanf, fscanf, fprintf, fopen, fclose
import exit msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

global start

segment data use32 class=data
    ; ...
    character dd 0
    input_descriptor dd 0
    output_descriptor dd 0
    input_file times 128 db 0
    output_file db "output.txt", 0
    word_buffer times 128 db 0
    char_fmt db " %c", 0
    string_fmt db "%s", 0
    string_nl_fmt db "%s", 10, 0
    read_mode db "r", 0
    write_mode db "w", 0

segment code use32 class=code
    start:
        ; ...
        ; read the input file name
        push input_file
        push string_fmt
        call [scanf]
        add esp, 4 * 2
        
        ; read the character to be searched
        push character
        push char_fmt
        call [scanf]
        add esp, 4 * 2
        
        ; open the input file
        push read_mode
        push input_file
        call [fopen]
        add esp, 4 * 2
        
        ; check for successful open and save the file descriptor
        cmp eax, 0
        je clean
        mov [input_descriptor], eax
        
        ;open the output file
        push write_mode
        push output_file
        call [fopen]
        add esp, 4 * 2
        
        ; check for successful open and save the file descriptor
        cmp eax, 0
        je clean
        mov [output_descriptor], eax
        
        ; read word by word from input and write it to output if character is found in word
        parse:
            ; read word from input file
            push word_buffer
            push string_fmt
            push dword [input_descriptor]
            call [fscanf]
            add esp, 4 * 3
            
            ; if there were no characters read it means we reached the end of file
            cmp eax, 0
            je parse_end
            
            ; mov the word address in esi and use ebx as a flag for remembering if the word contains the character
            mov esi, word_buffer
            mov ebx, 0
            check:
                ; load in al the word letter by letter and if al is 0 we reached the end of the word
                lodsb
                cmp al, 0
                je check_end
                
                ; compare the letter with the character and if they are equal set ebx to 1 and finish checking, otherwise continue checking
                cmp al, [character]
                jne check
                mov ebx, 1
                jmp check_end
            check_end:
            
            ; check if the word contains the character, if not, continue with the next word
            cmp ebx, 1
            jne parse
            
            ; if we are here it means that the word contains the character and we print it to the output file
            push word_buffer
            push string_nl_fmt
            push dword [output_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            ; continue parsing the next words
            jmp parse
        parse_end:
        
        ; close the input and output file descriptor
        clean:
        
        cmp dword [input_descriptor], 0
        je skip_input
        push dword [input_descriptor]
        call [fclose]
        add esp, 4
        skip_input:
        
        cmp dword [output_descriptor], 0
        je skip_output
        push dword [output_descriptor]
        call [fclose]
        add esp, 4
        skip_output:
        
        ; exit(0)
        push    dword 0
        call    [exit]
