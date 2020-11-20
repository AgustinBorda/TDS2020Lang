.file "ex.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	movq $1, %rax
	cmpq $0, %rax
	jz .t0
.t1:
	movq $0, %rax
	cmpq $0, %rax
	jz .t2
	jmp .t1
.t2:
	movq $1, %rax
	cmpq $0, %rax
	jz .t3
.t3:
	movq $1, %rax
	leave
	ret
	jmp .t5
.t0:
	movq $1, %rax
	cmpq $0, %rax
	jz .t6
.t6:
	movq $2, %rax
	leave
	ret
.t5:
.size main, .-main
