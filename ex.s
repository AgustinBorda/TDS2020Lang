.file "ex.ctds"
.text
.comm a,8,8
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq $5, %rax
	movq %rax, -8(%rbp)
	movq $0, %rax
	cmpq $0, %rax
	jz .t1
	movq $1, %rax
	movq %rax, -8(%rbp)
	movq 0(%rbp), %rax
	movq %rax, -16(%rbp)
.t1:
	movq -8(%rbp), %rax
	leave
	ret
.size main, .-main
.globl not
.type not, @function
not:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq a(%rip), %rax
	negq %rax
	and $0x1, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	leave
	ret
.size not, .-not