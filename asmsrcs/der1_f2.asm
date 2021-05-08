global der1_f2

section .text

der1_f2:
    push ebp
    mov ebp, esp
    
    push 2
    fild dword[esp]
    add esp, 4
    
    fchs
    
    mov esp, ebp
    pop ebp
    ret