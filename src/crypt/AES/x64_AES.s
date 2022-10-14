/*
*
*   src/AES/x64_AES.h
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
*
*   A collection of programs for cybersecurity competitions and practices
*   Copyright (C) 2022  Alicia Antó Valencía
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifdef __x86_64__

.section .text

.globl AES

# Optimized AES for x64 with AES instructions
AES:
    # Set up stack frame
    push %rbp
    mov %rsp, %rbp

    # Move state into xmm1
    movups (%rdi), %xmm1
    # Null rax, our offset register
    xor %rax, %rax

    # Round 1
    xorps (%rsi), %xmm1

    # Set up loop counter 
    mov $12, %rcx
.L1:
    # Loop for encryption
    dec %rcx
    add $16, %rax
    aesenc (%rsi, %rax), %xmm1
    cmp $0, %rcx
    jne .L1

    # Perform last round
    add $16, %rax
    aesenclast (%rsi, %rax), %xmm1

    # Move xmm1 into state
    movups %xmm1, (%rdi)

    # Undo stack frame and return
    mov %rbp, %rsp
    pop %rbp
    ret

#endif