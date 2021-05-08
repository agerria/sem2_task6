global der2_f2

section .text

der2_f2:
    push ebp
    mov ebp, esp
    
    push 0
    fild dword[esp]
    add esp, 4
    
    mov esp, ebp
    pop ebp
    ret