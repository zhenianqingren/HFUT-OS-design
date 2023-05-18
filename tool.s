	.file	"tool.c"
	.text
	.globl	parse
	.type	parse, @function
parse:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L8:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jne	.L3
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L5
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movzbl	1(%rdx), %edx
	movb	%dl, (%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	jmp	.L5
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L9
	movl	$-1, %eax
	jmp	.L7
.L9:
	nop
.L5:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L8
	movl	$0, %eax
.L7:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	parse, .-parse
	.globl	sys_call
	.type	sys_call, @function
sys_call:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L11
.L14:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L12
	movl	-4(%rbp), %eax
	jmp	.L13
.L12:
	addl	$1, -4(%rbp)
.L11:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L14
	movl	$-1, %eax
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	sys_call, .-sys_call
	.globl	transupper
	.type	transupper, @function
transupper:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L16
.L20:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$61, %al
	je	.L22
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rcx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$512, %eax
	testl	%eax, %eax
	je	.L19
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	toupper@PLT
	movl	%eax, %ecx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
.L19:
	addl	$1, -8(%rbp)
.L16:
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jl	.L20
	jmp	.L18
.L22:
	nop
.L18:
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	.L23
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
.L23:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	transupper, .-transupper
	.globl	output
	.type	output, @function
output:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L25
.L29:
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movl	-36(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jns	.L26
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$4, %eax
	jne	.L27
	movq	$0, -24(%rbp)
	jmp	.L26
.L27:
	call	__errno_location@PLT
	movl	(%rax), %eax
	jmp	.L28
.L26:
	movq	-24(%rbp), %rax
	subq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	addq	%rax, -16(%rbp)
.L25:
	cmpq	$0, -8(%rbp)
	jg	.L29
	movl	$0, %eax
.L28:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	output, .-output
	.section	.rodata
.LC0:
	.string	"detected\n"
	.text
	.globl	input
	.type	input, @function
input:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -24(%rbp)
	movl	$1, -20(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L31
.L39:
	cmpq	$0, -8(%rbp)
	jns	.L32
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$4, %eax
	je	.L32
	movl	$-1, %eax
	jmp	.L33
.L32:
	cmpq	$0, -8(%rbp)
	jns	.L34
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$4, %eax
	jne	.L34
	jmp	.L31
.L34:
	addl	$1, -24(%rbp)
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L35
	movq	-16(%rbp), %rax
	movb	$0, (%rax)
	movl	$0, -20(%rbp)
	jmp	.L36
.L35:
	movq	-48(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$27, %al
	jne	.L37
	movq	-48(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	cmpb	$91, %al
	jne	.L37
	movq	-48(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	cmpb	$65, %al
	jne	.L37
	movl	$9, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	call	output
	movl	$32, %eax
	jmp	.L33
.L37:
	movq	-48(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$27, %al
	jne	.L38
	movq	-48(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	cmpb	$91, %al
	jne	.L38
	movq	-48(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	cmpb	$66, %al
	jne	.L38
	movl	$64, %eax
	jmp	.L33
.L38:
	addq	$1, -16(%rbp)
.L31:
	movq	-16(%rbp), %rcx
	movl	-36(%rbp), %eax
	movl	$1, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L39
.L36:
	cmpl	$1, -20(%rbp)
	jne	.L40
	cmpl	$0, -24(%rbp)
	je	.L40
	movq	-48(%rbp), %rax
	movb	$0, (%rax)
	addl	$1, -24(%rbp)
.L40:
	movl	-24(%rbp), %eax
.L33:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	input, .-input
	.globl	push_front
	.type	push_front, @function
push_front:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	push_front, .-push_front
	.globl	push_back
	.type	push_back, @function
push_back:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	push_back, .-push_back
	.globl	strnode
	.type	strnode, @function
strnode:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	strnode, .-strnode
	.globl	self_strcmp
	.type	self_strcmp, @function
self_strcmp:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L46
.L51:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$61, %al
	jne	.L47
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L52
.L47:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L49
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	jmp	.L50
.L49:
	addl	$1, -4(%rbp)
.L46:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L51
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L51
	jmp	.L48
.L52:
	nop
.L48:
	movl	$0, %eax
.L50:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	self_strcmp, .-self_strcmp
	.globl	compch
	.type	compch, @function
compch:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %ecx
	movl	%esi, %eax
	movl	%edx, -12(%rbp)
	movl	%ecx, %edx
	movb	%dl, -4(%rbp)
	movb	%al, -8(%rbp)
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movsbq	-4(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L54
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movsbq	-8(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L54
	cmpl	$0, -12(%rbp)
	je	.L54
	movsbl	-4(%rbp), %eax
	movl	%eax, %edi
	call	toupper@PLT
	movb	%al, -4(%rbp)
	movsbl	-8(%rbp), %eax
	movl	%eax, %edi
	call	toupper@PLT
	movb	%al, -8(%rbp)
.L54:
	movsbl	-4(%rbp), %edx
	movsbl	-8(%rbp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	compch, .-compch
	.type	build_next, @function
build_next:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, -40(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, (%rax)
	movl	$0, -8(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L57
.L60:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	-40(%rbp), %edx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	compch
	testl	%eax, %eax
	jne	.L58
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	-8(%rbp), %edx
	addl	$1, %edx
	movl	%edx, (%rax)
	addl	$1, -4(%rbp)
	jmp	.L57
.L58:
	cmpl	$0, -8(%rbp)
	jne	.L57
	cmpl	$0, -8(%rbp)
	jne	.L59
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
	jmp	.L57
.L59:
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	leaq	-4(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -8(%rbp)
.L57:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L60
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	build_next, .-build_next
	.globl	kmp
	.type	kmp, @function
kmp:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$4160, %rsp
	movq	%rdi, -4136(%rbp)
	movq	%rsi, -4144(%rbp)
	movl	%edx, -4148(%rbp)
	movl	%ecx, -4152(%rbp)
	movl	%r8d, -4156(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	-4156(%rbp), %ecx
	movl	-4152(%rbp), %edx
	leaq	-4112(%rbp), %rsi
	movq	-4144(%rbp), %rax
	movq	%rax, %rdi
	call	build_next
	movl	$0, -4120(%rbp)
	movl	$0, -4116(%rbp)
	jmp	.L62
.L66:
	movl	-4116(%rbp), %eax
	movslq	%eax, %rdx
	movq	-4144(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %ecx
	movl	-4120(%rbp), %eax
	movslq	%eax, %rdx
	movq	-4136(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	-4156(%rbp), %edx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	compch
	testl	%eax, %eax
	jne	.L63
	addl	$1, -4120(%rbp)
	addl	$1, -4116(%rbp)
	jmp	.L62
.L63:
	cmpl	$0, -4116(%rbp)
	jle	.L64
	movl	-4116(%rbp), %eax
	subl	$1, %eax
	cltq
	movl	-4112(%rbp,%rax,4), %eax
	movl	%eax, -4116(%rbp)
	jmp	.L62
.L64:
	addl	$1, -4120(%rbp)
.L62:
	movl	-4120(%rbp), %eax
	cmpl	-4148(%rbp), %eax
	jge	.L65
	movl	-4116(%rbp), %eax
	cmpl	-4152(%rbp), %eax
	jl	.L66
.L65:
	movl	-4116(%rbp), %eax
	cmpl	-4152(%rbp), %eax
	sete	%al
	movzbl	%al, %eax
	movq	-8(%rbp), %rdi
	xorq	%fs:40, %rdi
	je	.L68
	call	__stack_chk_fail@PLT
.L68:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	kmp, .-kmp
	.globl	itos
	.type	itos, @function
itos:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movb	$0, (%rax)
	jmp	.L70
.L71:
	subq	$1, -16(%rbp)
	movl	-4(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	%edx, %eax
	addl	$48, %eax
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movb	%dl, (%rax)
	movl	-4(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -4(%rbp)
.L70:
	cmpl	$0, -4(%rbp)
	jne	.L71
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	itos, .-itos
	.globl	write_num
	.type	write_num, @function
write_num:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	leaq	31(%rax), %rdx
	movl	-68(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	itos
	movq	%rax, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	31(%rax), %rdx
	movq	-56(%rbp), %rax
	subq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	output
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L74
	call	__stack_chk_fail@PLT
.L74:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	write_num, .-write_num
	.globl	nread
	.type	nread, @function
nread:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
	jmp	.L76
.L80:
	cmpl	$-1, -4(%rbp)
	jne	.L77
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$4, %eax
	je	.L78
	movl	$-1, %eax
	jmp	.L79
.L78:
	movl	$0, -4(%rbp)
	jmp	.L76
.L77:
	movl	-4(%rbp), %eax
	subl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	addq	%rax, -32(%rbp)
.L76:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L80
	movl	-24(%rbp), %eax
	subl	-8(%rbp), %eax
.L79:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	nread, .-nread
	.local	save
	.comm	save,60,32
	.data
	.align 4
	.type	ttysavefd, @object
	.size	ttysavefd, 4
ttysavefd:
	.long	-1
	.local	ttystate
	.comm	ttystate,4,4
	.section	.rodata
.LC1:
	.string	"error\n"
	.text
	.globl	tty_cbreak
	.type	tty_cbreak, @function
tty_cbreak:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movl	%edi, -100(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	ttystate(%rip), %eax
	testl	%eax, %eax
	je	.L82
	call	__errno_location@PLT
	movl	$22, (%rax)
	movl	$-1, %eax
	jmp	.L89
.L82:
	leaq	-80(%rbp), %rdx
	movl	-100(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	tcgetattr@PLT
	testl	%eax, %eax
	jns	.L84
	movl	$6, %edx
	leaq	.LC1(%rip), %rsi
	movl	$2, %edi
	call	output
	movl	$-1, %eax
	jmp	.L89
.L84:
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, save(%rip)
	movq	%rdx, 8+save(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+save(%rip)
	movq	%rdx, 24+save(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+save(%rip)
	movq	%rdx, 40+save(%rip)
	movq	-32(%rbp), %rax
	movq	%rax, 48+save(%rip)
	movl	-24(%rbp), %eax
	movl	%eax, 56+save(%rip)
	movl	-68(%rbp), %eax
	andl	$-11, %eax
	movl	%eax, -68(%rbp)
	movb	$1, -57(%rbp)
	movb	$0, -58(%rbp)
	leaq	-80(%rbp), %rdx
	movl	-100(%rbp), %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	tcsetattr@PLT
	testl	%eax, %eax
	jns	.L85
	movl	$-1, %eax
	jmp	.L89
.L85:
	leaq	-80(%rbp), %rdx
	movl	-100(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	tcgetattr@PLT
	testl	%eax, %eax
	jns	.L86
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	%eax, -84(%rbp)
	movl	-100(%rbp), %eax
	leaq	save(%rip), %rdx
	movl	$2, %esi
	movl	%eax, %edi
	call	tcsetattr@PLT
	call	__errno_location@PLT
	movq	%rax, %rdx
	movl	-84(%rbp), %eax
	movl	%eax, (%rdx)
	movl	$-1, %eax
	jmp	.L89
.L86:
	movl	-68(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	jne	.L87
	movzbl	-57(%rbp), %eax
	cmpb	$1, %al
	jne	.L87
	movzbl	-58(%rbp), %eax
	testb	%al, %al
	je	.L88
.L87:
	movl	-100(%rbp), %eax
	leaq	save(%rip), %rdx
	movl	$2, %esi
	movl	%eax, %edi
	call	tcsetattr@PLT
	call	__errno_location@PLT
	movl	$22, (%rax)
	movl	$-1, %eax
	jmp	.L89
.L88:
	movl	$2, ttystate(%rip)
	movl	-100(%rbp), %eax
	movl	%eax, ttysavefd(%rip)
	movl	$0, %eax
.L89:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L90
	call	__stack_chk_fail@PLT
.L90:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	tty_cbreak, .-tty_cbreak
	.globl	tty_reset
	.type	tty_reset, @function
tty_reset:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	ttystate(%rip), %eax
	testl	%eax, %eax
	jne	.L92
	movl	$0, %eax
	jmp	.L93
.L92:
	movl	-4(%rbp), %eax
	leaq	save(%rip), %rdx
	movl	$2, %esi
	movl	%eax, %edi
	call	tcsetattr@PLT
	testl	%eax, %eax
	jns	.L94
	movl	$-1, %eax
	jmp	.L93
.L94:
	movl	$0, ttystate(%rip)
	movl	$0, %eax
.L93:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	tty_reset, .-tty_reset
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
