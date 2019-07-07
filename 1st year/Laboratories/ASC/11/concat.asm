bits 32

global concat

segment code use32 class=code
    ; void concat(char * dst, const char * src);
    ; append the contents of src to dsc
    concat:
        cld ; traverse left to right
        mov esi, [esp + 4] ; make esi point to the first string
        .traverse:
            lodsb
            cmp al, 0
            jnz .traverse ; traverse the first string untill the terminating character '\0' is met
        dec esi ; decrease esi to ovewrite the terminating character
        mov edi, esi ; move in edi the ending address of the first string
        mov esi, [esp + 8] ; make esi point to the second string
        .append:
            lodsb
            stosb
            cmp al, 0
            jnz .append ; append the second string to the first one
        ret
