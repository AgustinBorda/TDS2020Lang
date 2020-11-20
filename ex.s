.file "ex.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movq $0, %rax
	movq %rax, -8(%rbp)
.t1:
	movq -8(%rbp), %rax
	cmpq $256, %rax
	setl %al
	movzbq %al, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	cmpq $0, %rax
	jz .t3
	movq -8(%rbp), %rax
	addq $1, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	jmp .t1
.t3:
	movq -8(%rbp), %rax
	movq $-1, %rax
	leave
	ret
.size main, .-main
