global der2_f3

section .text

der2_f3:
    push ebp
    mov ebp, esp
    
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fmulp
    
    push 10
    fild dword[esp]
    add esp, 4
    
    fdivr
    fchs
    
    mov esp, ebp
    pop ebp
    ret