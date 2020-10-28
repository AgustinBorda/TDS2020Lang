	.file	"semantic_analyzer.c"
	.text
	.comm	has_return,4,4
	.comm	function_return_type,4,4
	.section	.rodata
.LC0:
	.string	"%s"
	.text
	.globl	type_error
	.type	type_error, @function
type_error:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE6:
	.size	type_error, .-type_error
	.section	.rodata
.LC1:
	.string	"="
	.align 8
.LC2:
	.string	"Type error: The variable must be the same type of expression\n"
.LC3:
	.string	"RETURN"
	.align 8
.LC4:
	.string	"Type error: return must be void\n"
	.align 8
.LC5:
	.string	"Type error: wrong type in return\n"
.LC6:
	.string	"!"
	.align 8
.LC7:
	.string	"Type error: The ! operator needs a bool type\n"
.LC8:
	.string	"&&"
	.align 8
.LC9:
	.string	"Type error: The && operator needs a bool type\n"
.LC10:
	.string	"=="
	.align 8
.LC11:
	.string	"Type error: The two expressions in == must be the same type\n"
	.align 8
.LC12:
	.string	"Type error: The two expresions in arithmetic operations must be integer\n"
	.text
	.globl	analyze_types
	.type	analyze_types, @function
analyze_types:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	32(%rax), %eax
	cmpl	$2, %eax
	jne	.L3
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L4
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	.L5
	movl	-8(%rbp), %eax
	jmp	.L2
.L5:
	leaq	.LC2(%rip), %rdi
	call	type_error
.L4:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L7
	movl	$1, has_return(%rip)
	movl	function_return_type(%rip), %eax
	cmpl	$2, %eax
	jne	.L8
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L9
	leaq	.LC4(%rip), %rdi
	call	type_error
.L9:
	movl	$2, %eax
	jmp	.L2
.L8:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L10
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	function_return_type(%rip), %edx
	cmpl	%edx, %eax
	je	.L11
.L10:
	leaq	.LC5(%rip), %rdi
	call	type_error
.L11:
	movl	function_return_type(%rip), %eax
	jmp	.L2
.L7:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L12
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	cmpl	$1, %eax
	je	.L13
	leaq	.LC7(%rip), %rdi
	call	type_error
.L13:
	movl	$1, %eax
	jmp	.L2
.L12:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC8(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L14
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -4(%rbp)
	cmpl	$1, -8(%rbp)
	jne	.L15
	cmpl	$1, -4(%rbp)
	jne	.L15
	movl	$1, %eax
	jmp	.L2
.L15:
	leaq	.LC9(%rip), %rdi
	call	type_error
.L14:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L16
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	.L17
	movl	$1, %eax
	jmp	.L2
.L17:
	leaq	.LC11(%rip), %rdi
	call	type_error
.L16:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	analyze_types
	movl	%eax, -4(%rbp)
	cmpl	$0, -8(%rbp)
	jne	.L18
	cmpl	$0, -4(%rbp)
	jne	.L18
	movl	$0, %eax
	jmp	.L2
.L18:
	leaq	.LC12(%rip), %rdi
	call	type_error
	jmp	.L2
.L3:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	(%rax), %eax
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	analyze_types, .-analyze_types
	.section	.rodata
.LC13:
	.string	";"
.LC14:
	.string	"FUN"
	.text
	.globl	analyze
	.type	analyze, @function
analyze:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC13(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L21
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L22
.L21:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L23
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	analyze
.L23:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L24
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	analyze
.L24:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L26
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	analyze
	jmp	.L26
.L22:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	analyze_types
	nop
.L26:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	analyze, .-analyze
	.section	.rodata
.LC15:
	.string	"return statement not found.\n"
	.text
	.globl	semantic_analyzer
	.type	semantic_analyzer, @function
semantic_analyzer:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, function_return_type(%rip)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, has_return(%rip)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	analyze
	movl	has_return(%rip), %eax
	testl	%eax, %eax
	jne	.L29
	leaq	.LC15(%rip), %rdi
	call	type_error
.L29:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	semantic_analyzer, .-semantic_analyzer
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
