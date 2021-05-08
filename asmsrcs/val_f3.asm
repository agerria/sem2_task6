global val_f3

section .text

val_f3:
    push ebp
    mov ebp, esp
    
    fld qword[ebp + 8]
    
    fchs
    
    push 5
    fild dword[esp]
    add esp, 4
    
    fdivr
    
    mov esp, ebp
    pop ebp
    ret