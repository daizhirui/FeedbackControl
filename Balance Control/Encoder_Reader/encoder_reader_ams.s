	.file	1 "encoder_reader.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg

	.comm	counter,4,4
	.text
	.align	2
	.globl	user_interrupt
	.set	nomips16
	.set	nomicromips
	.ent	user_interrupt
	.type	user_interrupt, @function
user_interrupt:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	lw	$2,%gp_rel(counter)($28)
	nop
	move	$4,$2
	jal	xtoa
	nop

	move	$4,$2
	jal	puts
	nop

	li	$4,10			# 0xa
	jal	putch
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x503
	li	$3,255			# 0xff
	sw	$3,0($2)
	nop
	move	$sp,$fp
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addiu	$sp,$sp,24
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
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x700
	li	$3,1			# 0x1
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x502
	sw	$0,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x500
	li	$3,4			# 0x4
	sw	$3,0($2)
	sw	$0,%gp_rel(counter)($28)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x704
	sw	$0,0($2)
$L7:
	sw	$0,16($fp)
	b	$L3
	nop

$L4:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x706
	lw	$2,0($2)
	nop
	andi	$2,$2,0x1
	sw	$2,16($fp)
	lw	$2,16($fp)
	nop
	move	$4,$2
	jal	xtoa
	nop

	move	$4,$2
	jal	puts
	nop

	li	$4,10			# 0xa
	jal	putch
	nop

$L3:
	lw	$2,16($fp)
	nop
	beq	$2,$0,$L4
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x706
	lw	$2,0($2)
	nop
	andi	$2,$2,0x2
	beq	$2,$0,$L5
	nop

	lw	$2,%gp_rel(counter)($28)
	nop
	addiu	$2,$2,-1
	sw	$2,%gp_rel(counter)($28)
	b	$L7
	nop

$L5:
	lw	$2,%gp_rel(counter)($28)
	nop
	addiu	$2,$2,1
	sw	$2,%gp_rel(counter)($28)
	b	$L7
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 7.1.0"
