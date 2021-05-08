%include "io.inc"

extern printf
section .rodata
    line db "%lf", 0x0
section .data
    num dq -1.0     ; input number
section .text
global CMAIN
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
CMAIN:
    push dword[num+4]
    push dword[num]
    call der2_f3
    add esp, 8
    
    sub esp, 12
    mov dword[esp], line
    fstp qword[esp+4]
    call printf
    add esp, 12
    
    xor eax, eax
    ret
