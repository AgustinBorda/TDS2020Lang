.file "test4.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	pushq %rdi
	movq $5, %rdi
	call fib
	movq %rax, -8(%rbp)
	popq %rdi
	movq -8(%rbp), %rax
	leave
	ret
.size main, .-main
.globl fib
.type fib, @function
fib:
	pushq %rbp
	movq %rsp, %rbp
	subq $48, %rsp
	movq $0, %rax
	movq %rax, -8(%rbp)
	movq $0, %rax
	movq %rax, -16(%rbp)
	movq $1, %rax
	movq %rax, -24(%rbp)
	movq $1, %rax
	movq %rax, -32(%rbp)
.t5:
	movq -32(%rbp), %rax
	cmpq %rdi, %rax
	setl %al
	movzbq %al, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	cmpq $0, %rax
	jz .t7
	movq -8(%rbp), %rax
	addq -24(%rbp), %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	movq %rax, -16(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	movq -16(%rbp), %rax
	movq %rax, -24(%rbp)
	jmp .t5
.t7:
	movq -24(%rbp), %rax
	leave
	ret
.size fib, .-fib
