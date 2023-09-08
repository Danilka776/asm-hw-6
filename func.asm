section .data
    tw dd 20.0
section .text
global f1 ;2^x+1
f1:
    push ebp
    mov ebp, esp
    
    fld qword[ebp+8]
    fld1
    fscale
    fxch
    fld1
    fxch
    fprem
    f2xm1
    faddp
    fmulp
    fld1
    faddp

    mov esp, ebp
    pop ebp
    ret
    
global df1 ;2^x*ln2
df1: 
    push ebp
    mov ebp, esp

    fld qword[ebp+8]
    fld1
    fscale
    fxch
    fld1
    fxch
    fprem
    f2xm1
    faddp
    fmulp
    fldln2
    fmulp

    mov esp, ebp
    pop ebp
    ret
 
global ddf1 ;2^x*ln2*ln2
ddf1:
    push ebp
    mov ebp, esp

    fld qword[ebp+8]
    fld1
    fscale
    fxch
    fld1
    fxch
    fprem
    f2xm1
    faddp
    fmulp
    fldln2
    fmulp
    fldln2
    fmulp

    mov esp, ebp
    pop ebp
    ret
           
global f2 ; x^5
f2:
    push ebp
    mov ebp, esp
    
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp

    mov esp, ebp
    pop ebp
    ret

global df2 ;5*x^4
df2:
    push ebp
    mov ebp, esp
    
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp
    fld1
    fld1
    faddp
    fld1
    faddp
    fld1
    faddp
    fld1
    faddp
    fmulp

    mov esp, ebp
    pop ebp
    ret

global ddf2 ;20*x^3
ddf2:
    push ebp
    mov ebp, esp

    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp
    fld dword[tw]
    fmulp

    mov esp, ebp
    pop ebp
    ret 
                   
global f3 ;(1-x)/3
f3:
    push ebp
    mov ebp, esp
    
    fld1
    fld qword[ebp+8]
    fsubp
    fld1
    fld1
    faddp
    fld1
    faddp
    fdivp

    mov esp, ebp
    pop ebp
    ret  
    
global df3 ;-1/3
df3:
    push ebp
    mov ebp, esp
    
    fldz
    fld1
    fsubp
    fld1
    fld1
    faddp
    fld1
    faddp
    fdivp

    mov esp, ebp
    pop ebp
    ret
    
global ddf3 ;0
ddf3:
    push ebp
    mov ebp, esp
    
    fldz

    mov esp, ebp
    pop ebp
    ret                                     