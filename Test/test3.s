.file "test3.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	pushq %rsi
	movq $6, %rsi
	pushq %rdi
	movq $5, %rdi
	call max
	movq %rax, -8(%rbp)
	popq %rdi
	popq %rsi
	movq -8(%rbp), %rax
	leave
	ret
.size main, .-main
.globl max
.type max, @function
max:
	pushq %rbp
	movq %rsp, %rbp
	movq %rdi, %rax
	cmpq %rsi, %rax
	setl %al
	movzbq %al, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	cmpq $0, %rax
	jz .t2
	movq %rsi, %rax
	leave
	ret
	jmp .t4
.t2:
	movq %rdi, %rax
	leave
	ret
.t4:
.size max, .-max
