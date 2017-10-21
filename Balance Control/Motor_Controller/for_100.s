	.file	1 "for.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.align	2
	.globl	user_interrupt
	.set	nomips16
	.set	nomicromips
	.ent	user_interrupt
	.type	user_interrupt, @function		# we don't need it.
user_interrupt:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	nop
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	user_interrupt
	.size	user_interrupt, .-user_interrupt
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16		# initialize a 16-byte stack
	sw	$fp,12($sp)			# store $fp to stack[12]
	move	$fp,$sp			# $fp = $sp, store the stack pointer to frame pointer
	sw	$0,0($fp)			# store 0 to stack[0]
	b	$L3
	nop

$L4:
	lw	$2,0($fp)
	nop
	addiu	$2,$2,1
	sw	$2,0($fp)
$L3:
	lw	$2,0($fp)			# load stack[0]=0 to $2
	nop
	slt	$2,$2,100			# set $2 = 1 if ($2 < 100)
	bne	$2,$0,$L4			# brach to $L4 if ($2 != 0)
	nop

	nop
	move	$sp,$fp			# $sp = $fp, recover $sp
	lw	$fp,12($sp)			# $fp = stack[12], recover $fp
	addiu	$sp,$sp,16		# release the 16-byte stack
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 7.1.0"
