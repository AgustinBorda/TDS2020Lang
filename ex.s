.file "ex.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	call fun
	movq %rax, -8(%rbp)
	pushq %rsi
	movq $1, %rsi
	call fun1
	movq %rax, -16(%rbp)
	pushq %rsi
	movq (null), %rax
	movq %rax, -24(%rbp)
	movq $0, %rax
	leave
	ret
.size main, .-main
.globl fun1
.type fun1, @function
fun1:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq $0, %rax
	movq %rax, -8(%rbp)
.t3:
	movq -8(%rbp), %rax
	cmpq %rsi, %rax
	setl %al
	movzbq %al, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	cmpq $0, %rax
	jz .t5
	movq -8(%rbp), %rax
	addq $1, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	jmp .t3
.t5:
	movq -8(%rbp), %rax
	leave
	ret
.size fun1, .-fun1
.globl fun
.type fun, @function
fun:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq $0, %rax
	cmpq $0, %rax
	jz .t9
	movq $1, %rax
	leave
	ret
	jmp .t11
.t9:
	movq $0, %rax
	leave
	ret
.t11:
.size fun, .-fun
.globl or
.type or, @function
or:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq %rsi, %rax
	addq %rdi, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	leave
	ret
.size or, .-or
