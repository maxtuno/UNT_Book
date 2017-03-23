;///////////////////////////////////////////////////////////////////////////////
;//        copyright (c) 2012-2017 Oscar Riveros. all rights reserved.        //
;//                           oscar.riveros@peqnp.com                         //
;//                                                                           //
;//    without any restriction, Oscar Riveros reserved rights, patents and    //
;//  commercialization of this knowledge or derived directly from this work.  //
;///////////////////////////////////////////////////////////////////////////////

extern _malloc

section .text

global _universal_new
_universal_new:
    mov        edi, 0x10
    jmp        _malloc


global _universal_from_string
_universal_from_string:
    push       r12
    push       rbp
    xor        eax, eax
    push       rbx
    xor        r12d, r12d
    mov        rbx, rdi
    call       _universal_new
    mov        rbp, rax

l9c9:
    lea        rax, [r12+1]
    cmp        byte [rbx+rax-1], 0x30
    jne        l9da

    mov        r12, rax
    jmp        l9c9

l9da:
    xor        eax, eax
    or         rcx, 0xffffffffffffffff
    mov        rdi, rbx
    repne      scasb
    mov        rdx, rcx
    not        rdx
    lea        rdi, [rdx-1]
    sub        rdi, r12
    test       rdi, rdi
    mov        qword [rbp+8], rdi
    jne        la16

    mov        qword [rbp+8], 0x1
    mov        edi, 0x1
    call       _malloc
    mov        qword [rbp], rax
    mov        byte [rax], 0x0
    jmp        la3d

la16:
    call       _malloc
    add        rbx, r12
    mov        qword [rbp], rax
    xor        eax, eax

la24:
    cmp        rax, qword [rbp+8]
    jae        la3d

    mov        sil, byte [rbx+rax]
    mov        rcx, qword [rbp]
    lea        edx, [rsi-0x30]
    mov        byte [rcx+rax], dl
    inc        rax
    jmp        la24

la3d:
    mov        rax, rbp
    pop        rbx
    pop        rbp
    pop        r12
    ret

global _universal_to_string
_universal_to_string:
    push       rbp
    push       rbx
    mov        rbp, rdi
    sub        rsp, 0x8
    mov        rbx, qword [rdi+8]
    mov        rdi, rbx
    call       _malloc
    xor        edx, edx

la5c:
    cmp        rdx, rbx
    je         la73

    mov        rcx, qword [rbp]
    mov        cl, byte [rcx+rdx]
    add        ecx, 0x30
    mov        byte [rax+rdx], cl
    inc        rdx
    jmp        la5c

la73:
    pop        rdx
    pop        rbx
    pop        rbp
    ret

global _universal_add
_universal_add:
    push       r13
    push       r12
    mov        r13, rsi
    push       rbp
    push       rbx
    mov        r12, rdi
    xor        eax, eax
    sub        rsp, 0x8
    call       _universal_new
    mov        rbp, qword [r12+8]
    cmp        qword [r13+8], rbp
    mov        rbx, rax
    cmovge     rbp, qword [r13+8]
    lea        rdi, [rbp+1]
    mov        qword [rax+8], rdi
    call       _malloc
    mov        qword [rbx], rax
    mov        rax, qword [r13+8]
    xor        r9d, r9d
    mov        sil, 0xa
    lea        rdx, [rax-1]
    mov        rax, qword [r12+8]
    lea        rcx, [rax-1]

lac6:
    mov        rax, rdx
    mov        r8, rcx
    not        rax
    not        r8
    shr        rax, 0x3f
    shr        r8, 0x3f
    mov        dil, al
    or         dil, r8b
    mov        rdi, qword [rbx]
    je         lb38

lae5:
    test       r8b, r8b
    je         laff

    test       al, al
    je         laff

    mov        r8, qword [r12]
    mov        rax, qword [r13]
    mov        al, byte [rax+rdx]
    add        al, byte [r8+rcx]
    jmp        lb1b

laff:
    test       rcx, rcx
    js         lb0d

    mov        rax, qword [r12]
    mov        al, byte [rax+rcx]
    jmp        lb1b

lb0d:
    xor        eax, eax
    test       rdx, rdx
    js         lb1b

    mov        rax, qword [r13]
    mov        al, byte [rax+rdx]

lb1b:
    add        eax, r9d
    dec        rcx
    dec        rdx
    movzx      eax, al
    div        sil
    mov        r9b, al
    movzx      eax, ah
    mov        byte [rdi+rbp], al
    dec        rbp
    jmp        lac6

lb38:
    test       r9b, r9b
    jne        lae5

    cmp        byte [rdi], 0x0
    jne        lb4c

    dec        qword [rbx+8]
    inc        rdi
    mov        qword [rbx], rdi

lb4c:
    pop        rdx
    mov        rax, rbx
    pop        rbx
    pop        rbp
    pop        r12
    pop        r13
    ret

global _universal_multiply
_universal_multiply:
    push       r12
    push       rbp
    mov        r12, rsi
    push       rbx
    mov        rbp, rdi
    xor        eax, eax
    call       _universal_new
    mov        rdi, qword [r12+8]
    add        rdi, qword [rbp+8]
    mov        rbx, rax
    mov        qword [rax+8], rdi
    shl        rdi, 0x2
    call       _malloc
    mov        qword [rbx], rax
    xor        eax, eax

lb86:
    cmp        rax, qword [rbx+8]
    jae        lb98

    mov        rdx, qword [rbx]
    mov        byte [rdx+rax], 0x0
    inc        rax
    jmp        lb86

lb98:
    mov        rax, qword [rbp+8]
    mov        r9b, 0xa
    lea        r8, [rax-1]
    xor        eax, eax

lba5:
    test       r8, r8
    js         lc25

    mov        rcx, qword [rbx+8]
    lea        esi, [rax+1]
    xor        edx, edx
    dec        rcx
    sub        rcx, rax
    mov        rax, qword [r12+8]
    lea        rdi, [rax-1]

lbc2:
    mov        rax, rdi
    sub        rax, 0x0
    js         lc18

lbcb:
    xor        eax, eax
    test       rdi, rdi
    js         lbe2

    mov        rax, qword [rbp]
    mov        r10, qword [r12]
    mov        al, byte [rax+r8]
    mul        byte [r10+rdi]

lbe2:
    add        eax, edx
    mov        r10, rcx
    dec        rdi
    movzx      eax, al
    div        r9b
    mov        edx, eax
    mov        rax, rcx
    add        rax, qword [rbx]
    dec        rcx
    mov        r11, rax
    movzx      eax, dh
    add        byte [r11], al
    add        r10, qword [rbx]
    movzx      eax, byte [r10]
    div        r9b
    add        edx, eax
    movzx      eax, ah
    mov        byte [r10], al
    jmp        lbc2

lc18:
    test       dl, dl
    jne        lbcb

    dec        r8
    movzx      eax, sil
    jmp        lba5

lc25:
    mov        rax, qword [rbx]
    cmp        byte [rax], 0x0
    jne        lc39

    inc        rax
    dec        qword [rbx+8]
    mov        qword [rbx], rax
    jmp        lc25

lc39:
    mov        rax, rbx
    pop        rbx
    pop        rbp
    pop        r12
    ret

