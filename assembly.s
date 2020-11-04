.file "assembly.c"
.text
.comm y,8,8
.comm x,8,8
	.globl main
	.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movq %rax, $7
	movq %rax, -8(%rbp)
	movq %rax, $5
	movq %rax, -16(%rbp)
	movq %rax, 0(%rbp)
	addq 0(%rbp), %rax
	movq %rax, -24(%rbp)
	movq %rax, -24(%rbp)
	leave
	ret
	.size	main, .-main
