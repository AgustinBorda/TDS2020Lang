.file "test1.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	pushq %rsi
	movq $8, %rsi
	pushq %rdi
	movq $6, %rdi
	call dif
	movq %rax, -8(%rbp)
	popq %rdi
	popq %rsi
	movq -8(%rbp), %rax
	leave
	ret
.size main, .-main
.globl dif
.type dif, @function
dif:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movq %rsi, %rax
	subq %rdi, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	cmpq $0, %rax
	setl %al
	movzbq %al, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	cmpq $0, %rax
	jz .t4
	movq $0, %rax
	subq $1, %rax
	movq %rax, -32(%rbp)
	movq -16(%rbp), %rax
	imulq -32(%rbp), %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	leave
	ret
	jmp .t8
.t4:
	movq -16(%rbp), %rax
	leave
	ret
.t8:
.size dif, .-dif
