	.file	1 "spi_c_test.c"
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
	.type	user_interrupt, @function
user_interrupt:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
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
	.globl	master
	.set	nomips16
	.set	nomicromips
	.ent	master
	.type	master, @function
master:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x804
	li	$3,16			# 0x10
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd04
	li	$3,4			# 0x4
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd04
	li	$3,6			# 0x6
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd03
	li	$3,1			# 0x1
	sw	$3,0($2)
 #APP
 # 12 "spi_c_test.c" 1
	nop
 # 0 "" 2
 #NO_APP
.L6:
	.set	noreorder
	nop
	.set	reorder
.L3:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd01
	lw	$2,0($2)
	#nop
	bne	$2,$0,.L3
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd02
	li	$3,65			# 0x41
	sw	$3,0($2)
	.set	noreorder
	nop
	.set	reorder
.L4:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd01
	lw	$2,0($2)
	#nop
	bne	$2,$0,.L4
	.set	noreorder
	nop
	.set	reorder
.L5:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd05
	lw	$2,0($2)
	#nop
	beq	$2,$0,.L5
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd00
	lw	$2,0($2)
	#nop
	sb	$2,16($fp)
	lbu	$2,16($fp)
	#nop
	move	$4,$2
	jal	putch
	b	.L6
	.end	master
	.size	master, .-master
	.align	2
	.globl	slave
	.set	nomips16
	.set	nomicromips
	.ent	slave
	.type	slave, @function
slave:
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
	ori	$2,$2,0x804
	li	$3,16			# 0x10
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd04
	sw	$0,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd03
	li	$3,1			# 0x1
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd02
	li	$3,66			# 0x42
	sw	$3,0($2)
.L9:
	nop
.L8:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd05
	lw	$2,0($2)
	nop
	beq	$2,$0,.L8
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd00
	lw	$2,0($2)
	nop
	sb	$2,16($fp)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd02
	li	$3,66			# 0x42
	sw	$3,0($2)
	lbu	$2,16($fp)
	nop
	move	$4,$2
	jal	putch
	nop

	b	.L9
	nop

	.set	macro
	.set	reorder
	.end	slave
	.size	slave, .-slave
	.rdata
	.align	2
.LC0:
	.ascii	"1=Master,0=Slave\012\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	lui	$2,%hi(.LC0)
	addiu	$4,$2,%lo(.LC0)
	jal	puts
	nop

	jal	getch
	nop

	li	$3,48			# 0x30
	beq	$2,$3,.L12
	nop

	li	$3,49			# 0x31
	beq	$2,$3,.L13
	nop

	b	.L10
	nop

.L12:
	jal	slave
	nop

	b	.L10
	nop

.L13:
	jal	master
	nop

.L10:
	move	$sp,$fp
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Codescape GNU Tools 2015.01-7 for MIPS MTI Bare Metal) 4.9.2"
