.file "test5.ctds"
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
	call equals_num
	movq %rax, -8(%rbp)
	popq %rdi
	popq %rsi
	movq -8(%rbp), %rax
	cmpq $0, %rax
	jz .t0
	movq $0, %rax
	leave
	ret
	jmp .t2
.t0:
	movq $1, %rax
	leave
	ret
.t2:
.size main, .-main
.globl equals_num
.type equals_num, @function
equals_num:
	pushq %rbp
	movq %rsp, %rbp
	movq %rdi, %rax
	cmpq %rsi, %rax
	sete %al
	movzbq %al, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	cmpq $0, %rax
	jz .t5
	movq $1, %rax
	leave
	ret
	jmp .t7
.t5:
	movq $0, %rax
	leave
	ret
.t7:
.size equals_num, .-equals_num
