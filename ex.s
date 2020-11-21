.file "ex.ctds"
.text
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq $1, %rax
	movq %rax, -8(%rbp)
	movq $0, %rax
	leave
	ret
.size main, .-main
.globl neg
.type neg, @function
neg:
	pushq %rbp
	movq %rsp, %rbp
	leave
	ret
.size neg, .-neg
