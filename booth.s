	.file	"booth.c"
	.text
	.globl	isub
	.def	isub;	.scl	2;	.type	32;	.endef
	.seh_proc	isub
isub:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	24(%rbp), %eax
	negl	%eax
	movl	%eax, 24(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	imul
	.def	imul;	.scl	2;	.type	32;	.endef
	.seh_proc	imul
imul:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L4
.L7:
	movl	16(%rbp), %eax
	andl	$1, %eax
	movl	%eax, -16(%rbp)
	cmpl	$1, -16(%rbp)
	jne	.L5
	cmpl	$0, -8(%rbp)
	jne	.L5
	movl	24(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	isub
	movl	%eax, -4(%rbp)
	jmp	.L6
.L5:
	cmpl	$0, -16(%rbp)
	jne	.L6
	cmpl	$1, -8(%rbp)
	jne	.L6
	movl	24(%rbp), %eax
	addl	%eax, -4(%rbp)
.L6:
	movl	-16(%rbp), %eax
	movl	%eax, -8(%rbp)
	sarl	16(%rbp)
	sall	24(%rbp)
	addl	$1, -12(%rbp)
.L4:
	cmpl	$31, -12(%rbp)
	jle	.L7
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "%d %d\0"
.LC1:
	.ascii "%d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	leaq	-12(%rbp), %rdx
	leaq	-8(%rbp), %rax
	leaq	.LC0(%rip), %rcx
	movq	%rdx, %r8
	movq	%rax, %rdx
	call	scanf
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %ecx
	call	imul
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leaq	.LC1(%rip), %rcx
	movl	%eax, %edx
	call	printf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev13, Built by MSYS2 project) 15.2.0"
	.def	scanf;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
