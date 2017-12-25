// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CSTRING_MEMCPY_MEMCPY_S
#define INCLUDED_SROOK_CSTRING_MEMCPY_MEMCPY_S

#if defined(__x86_64__) && defined(__linux__) && !defined(__CYGWIN__)

    .file   "memcpy.S"
    .text

    .type   _memcpy_short, @function
_memcpy_short:
.LSHORT:
    .cfi_startproc
    test    %edx, edx
    jz      .LEND

    movzbl  (%rsi), %ecx
    sub     $4, %edx
    jb      .LS4

    mov     (%rsi), %ecx
    mov     (%rsi, %rdx), %edi
    mov     %ecx, (%rax)
    mov     %edi, (%rax, %rdx)
.LEND:
    rep
    ret
    nop
.LS4
    mov     %cl, (%rax)
    add     $2, %edx
    jnc     .LEND
    movzwl  (%rsi, %rdx), %ecx
    mov     %cx, (%rax, %rdx)
    ret

    .cfi_endproc
    .size   _memcpy_short, .-_memcpy_short

/*
 *
 * memcpy: It uses AVX when __AVX__ is defined, and uses SSE2 otherwise.
 *
 */

    .align  16
    .globl  memcpy
    .type   memcpy, @function
memcpy:
    .cfi_startproc

    mov     %rdx, %rcx
    mov     %rdi, %rax
    cmp     $8, %rdx
    jb      .LSHORT
    mov     -8(%rsi, %rdx), %r8
    mov     (%rsi), %r9
    mov     %r8, -8(%rdi, %rdx)
    and     $24, %rcx
    jz      .L32

    mov     %r9, (%rdi)
    mov     %rcx, %r8
    sub     $16, %rcx
    jb      .LT32
#ifndef __AVX__
    movdqu  (%rsi, %rcx), %xmm1
    movdqu  %xmm1, (%rdi, %rcx)
#else
    vmovdqu (%rsi, %rcx), %xmm1
    vmovdqu (%xmm1, (%rdi, %rcx)
#endif

.LT32:
    add     %r8, %rsi
    and     $-32, %rdx
    jnz     .L32_adjDI
    ret

    .align  16

.L32_adjDI
    add     %r8, %rdi

.L32:
#ifndef __AVX__
    movdqu    (%rsi), %xmm0
    movdqu    16(%rsi), %xmm1
#else
    vmovdqu   (%rsi), %ymm0
#endif
    shr       $6, %rdx
    jnc       .L64_32read
#ifndef __AVX__
    movdqu    %xmm0, (%rdi)
    movdqu    %xmm1, 16(%rdi)
#else
    vmovdqu   %ymm0, (%rdi)
#endif
    lea       32(%rsi), %rsi
    jnz       .L64_adjDI

#ifdef __AVX__
    vzeroupper
#endif
    ret

.L64_adjDI:
    add       $32, %rdi

.L64:
#ifndef __AVX__
    movdqu    (%rsi), %xmm0
    movdqu    16(%rsi), %xmm1
#else
    vmovdqu   (%rsi), %ymm0
#endif

.L64_32read:
#ifndef __AVX__
    movdqu    32(%rsi), %xmm2
    movdqu    48(%rsi), %xmm3
    add       $64, %rsi
    movdqu    %xmm0, (%rdi)
    movdqu    %xmm1, 16(%rdi)
    movdqu    %xmm2, 32(%rdi)
    movdqu    %xmm3, 48(%rdi)
#else
    vmovdqu   32(%rsi), %ymm1
    add       $64, %rsi
    vmovdqu   %ymm0, (%rdi)
    vmovdqu   %ymm1, 32(%rdi)
#endif
    add       $64, %rdi
    dec       %rdx
    jnz       .L64

#ifdef __AVX__
    vzeroupper
#endif
     ret
.cfi_endproc
.size memcpy, .-memcpy

#endif
#endif
