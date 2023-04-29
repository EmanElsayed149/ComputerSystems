	.file	"main.c"
	.text
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB0:
	.cfi_startproc
	movq	%rdi, %rdx
	subq	%rsi, %rdx
	movq	%rsi, %rax
	subq	%rdi, %rax
	cmpq	%rsi, %rdi
	cmovge	%rdx, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	absdiff, .-absdiff
	.globl	fast_do
	.type	fast_do, @function
fast_do:
.LFB1:
	.cfi_startproc
	movl	$1, %eax
.L5:
	imulq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jg	.L5
	ret
	.cfi_endproc
.LFE1:
	.size	fast_do, .-fast_do
	.globl	fact_while
	.type	fact_while, @function
fact_while:
.LFB2:
	.cfi_startproc
	cmpq	$1, %rdi
	jle	.L10
	movl	$1, %eax
.L9:
	imulq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jne	.L9
	ret
.L10:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	fact_while, .-fact_while
	.globl	switch_eg_impl
	.type	switch_eg_impl, @function
switch_eg_impl:
.LFB3:
	.cfi_startproc
	subq	$100, %rsi
	cmpq	$6, %rsi
	ja	.L13
	leaq	jt.0(%rip), %rax
	jmp	*(%rax,%rsi,8)
.L14:
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rdi,%rax,4), %rdi
	jmp	.L15
.L16:
	addq	$10, %rdi
.L17:
	addq	$11, %rdi
	jmp	.L15
.L18:
	imulq	%rdi, %rdi
	jmp	.L15
.L13:
	movl	$0, %edi
.L15:
	movq	%rdi, (%rdx)
	ret
	.cfi_endproc
.LFE3:
	.size	switch_eg_impl, .-switch_eg_impl
	.globl	switcher
	.type	switcher, @function
switcher:
.LFB4:
	.cfi_startproc
	cmpq	$7, %rdi
	ja	.L24
	leaq	.L22(%rip), %r8
	movslq	(%r8,%rdi,4), %rax
	addq	%r8, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L22:
	.long	.L23-.L22
	.long	.L24-.L22
	.long	.L21-.L22
	.long	.L24-.L22
	.long	.L24-.L22
	.long	.L26-.L22
	.long	.L24-.L22
	.long	.L21-.L22
	.text
.L26:
	movl	$10, %edx
.L23:
	leaq	112(%rdx), %rsi
.L24:
	movq	%rsi, (%rcx)
	ret
.L21:
	addq	%rdx, %rdi
	leaq	0(,%rdi,4), %rsi
	jmp	.L24
	.cfi_endproc
.LFE4:
	.size	switcher, .-switcher
	.globl	fix_prod_ele
	.type	fix_prod_ele, @function
fix_prod_ele:
.LFB5:
	.cfi_startproc
	salq	$6, %rdx
	addq	%rdx, %rdi
	leaq	(%rsi,%rcx,4), %rax
	leaq	1024(%rax), %rsi
	movl	$0, %ecx
.L28:
	movl	(%rdi), %edx
	imull	(%rax), %edx
	addl	%edx, %ecx
	addq	$4, %rdi
	addq	$64, %rax
	cmpq	%rsi, %rax
	jne	.L28
	movl	%ecx, %eax
	ret
	.cfi_endproc
.LFE5:
	.size	fix_prod_ele, .-fix_prod_ele
	.globl	var_prod_ele
	.type	var_prod_ele, @function
var_prod_ele:
.LFB6:
	.cfi_startproc
	testq	%rdi, %rdi
	jle	.L33
	imulq	%rdi, %rcx
	leaq	(%rsi,%rcx,4), %r10
	leaq	0(,%rdi,4), %r9
	leaq	(%rdx,%r8,4), %rcx
	movl	$0, %esi
	movl	$0, %eax
.L32:
	movl	(%r10,%rax,4), %edx
	imull	(%rcx), %edx
	addl	%edx, %esi
	addq	$1, %rax
	addq	%r9, %rcx
	cmpq	%rax, %rdi
	jne	.L32
.L30:
	movl	%esi, %eax
	ret
.L33:
	movl	$0, %esi
	jmp	.L30
	.cfi_endproc
.LFE6:
	.size	var_prod_ele, .-var_prod_ele
	.section	.data.rel.ro.local,"aw"
	.align 32
	.type	jt.0, @object
	.size	jt.0, 56
jt.0:
	.quad	.L14
	.quad	.L13
	.quad	.L16
	.quad	.L17
	.quad	.L18
	.quad	.L13
	.quad	.L18
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
