global val_f2

section .text

val_f2:
    push ebp
    mov ebp, esp
    
    fld qword[ebp + 8]
    
    push 2
    fild dword[esp]
    add esp, 4
    fmulp
    
    fchs
    
    push 8
    fild dword[esp]
    add esp, 4
    faddp
    
    mov esp, ebp
    pop ebp
    ret