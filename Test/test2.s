.file "test2.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	pushq %rsi
	movq $5, %rsi
	pushq %rdi
	movq $5, %rdi
	call prod
	movq %rax, -8(%rbp)
	popq %rdi
	popq %rsi
	movq -8(%rbp), %rax
	leave
	ret
.size main, .-main
.globl prod
.type prod, @function
prod:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movq $0, %rax
	movq %rax, -8(%rbp)
.t2:
	movq -8(%rbp), %rax
	cmpq %rsi, %rax
	setl %al
	movzbq %al, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	cmpq $0, %rax
	jz .t4
	movq %rdi, %rax
	addq %rsi, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -32(%rbp)
	movq -8(%rbp), %rax
	addq $1, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	movq %rax, -8(%rbp)
	jmp .t2
.t4:
	movq -32(%rbp), %rax
	leave
	ret
.size prod, .-prod
