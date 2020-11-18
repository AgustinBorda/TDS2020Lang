.file "ex.ctds"
.text
.comm a,8,8
.globl fact
.type fact, @function
fact:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq $5, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	imulq -8(%rbp), %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	leave
	ret
.size fact, .-fact
.globl main
.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movq $1, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %rax, -16(%rbp)
	movq $0, %rax
	andq $1, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
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
