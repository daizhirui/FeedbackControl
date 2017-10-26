	.file	1 "array.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,112,$31		# vars= 104, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-112
	sw	$fp,108($sp)
	move	$fp,$sp
	li	$2,99			# 0x63
	sw	$2,0($fp)
	b	$L2
	nop

$L3:
	lw	$2,0($fp)
	nop
	addu	$2,$fp,$2
	li	$3,97			# 0x61
	sb	$3,4($2)
	lw	$2,0($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,0($fp)
$L2:
	lw	$2,0($fp)
	nop
	bne	$2,$0,$L3
	nop

	nop
	move	$sp,$fp
	lw	$fp,108($sp)
	addiu	$sp,$sp,112
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 7.1.0"
