extern exp

global f1
global f2
global f3

global f1_der
global f2_der
global f3_der

section .rodata
    num3 dq 3.0
    num2 dq 2.0

section .text

; y = e ^ (-x) + 3
;
; double f1 (double a)
f1: 
    finit
    push ebp
    mov ebp, esp

    and esp, ~15
    sub esp, 16

    fld qword[ebp + 8]
    fchs
    fstp qword[esp]
    call exp

    fld qword[num3]
    faddp

    leave
    ret


; y = 2x - 2
;
; double f2 (double a)
f2:
    finit
    push ebp
    mov ebp, esp

    fld qword[ebp + 8]
    fld1
    fsubp

    fld qword[num2]
    fmulp

    leave
    ret


; y = 1 / x
;
; double f3 (double a)
f3:
    finit
    push ebp
    mov ebp, esp

    fld1
    fld qword[ebp + 8]
    fdivp

    leave
    ret

 
; y = -e ^ (-x)
;
; double f1_der (double a)
f1_der:
    finit
    push ebp
    mov ebp, esp

    and esp, ~15
    sub esp, 16

    fld qword[ebp + 8]
    fchs
    fstp qword[esp]
    call exp
    fchs

    leave
    ret


; y = 2
;
; double f2_der (double a)
f2_der:
    finit
    push ebp
    mov ebp, esp

    fld qword[num2]

    leave
    ret


; y = -1 / (x ^ 2)
;
; double f3_der (double a)
f3_der:
    finit
    push ebp
    mov ebp, esp

    fld1
    fchs
    fld qword[ebp + 8]
    fdivp
    fld qword[ebp + 8]
    fdivp

    leave
    ret
