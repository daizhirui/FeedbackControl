	.file	1 "spi.c"
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
	.rdata
	.align	2
$LC0:
	.ascii	"Please input:\000"
	.align	2
$LC1:
	.ascii	"\012\000"
	.text
	.align	2
	.globl	SPI_Master_Mode
	.set	nomips16
	.set	nomicromips
	.ent	SPI_Master_Mode
	.type	SPI_Master_Mode, @function
SPI_Master_Mode:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
$L9:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd04
	li	$3,6			# 0x6
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x804
	li	$3,16			# 0x10
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd03
	li	$3,6			# 0x6
	sw	$3,0($2)
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	jal	puts
	nop

	nop
$L3:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x5
	lw	$2,0($2)
	nop
	beq	$2,$0,$L3
	nop

	li	$2,528482304			# 0x1f800000
	lw	$2,0($2)
	nop
	sw	$2,20($fp)
	nop
$L4:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd01
	lw	$2,0($2)
	nop
	bne	$2,$0,$L4
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd02
	lw	$3,20($fp)
	nop
	sw	$3,0($2)
	nop
$L5:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd01
	lw	$2,0($2)
	nop
	bne	$2,$0,$L5
	nop

	sw	$0,16($fp)
	b	$L6
	nop

$L7:
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L6:
	lw	$2,16($fp)
	nop
	slt	$2,$2,2
	bne	$2,$0,$L7
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd04
	li	$3,4			# 0x4
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd03
	li	$3,6			# 0x6
	sw	$3,0($2)
	nop
$L8:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x1
	lw	$2,0($2)
	nop
	bne	$2,$0,$L8
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x2
	lw	$3,20($fp)
	nop
	sw	$3,0($2)
	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	jal	puts
	nop

	b	$L9
	nop

	.set	macro
	.set	reorder
	.end	SPI_Master_Mode
	.size	SPI_Master_Mode, .-SPI_Master_Mode
	.rdata
	.align	2
$LC2:
	.ascii	"Input:\011\000"
	.text
	.align	2
	.globl	SPI_Slave_Mode
	.set	nomips16
	.set	nomicromips
	.ent	SPI_Slave_Mode
	.type	SPI_Slave_Mode, @function
SPI_Slave_Mode:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
$L13:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x804
	li	$3,16			# 0x10
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd04
	sw	$0,0($2)
	nop
$L11:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd05
	lw	$2,0($2)
	nop
	beq	$2,$0,$L11
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xd00
	lw	$2,0($2)
	nop
	sw	$2,16($fp)
	lui	$2,%hi($LC2)
	addiu	$4,$2,%lo($LC2)
	jal	puts
	nop

	nop
$L12:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x1
	lw	$2,0($2)
	nop
	bne	$2,$0,$L12
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x2
	lw	$3,16($fp)
	nop
	sw	$3,0($2)
	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	jal	puts
	nop

	b	$L13
	nop

	.set	macro
	.set	reorder
	.end	SPI_Slave_Mode
	.size	SPI_Slave_Mode, .-SPI_Slave_Mode
	.rdata
	.align	2
$LC3:
	.ascii	"Please choose a Mode:\012\000"
	.align	2
$LC4:
	.ascii	"(1) SPI_Master_Mode\012\000"
	.align	2
$LC5:
	.ascii	"(2) SPI_Slave_Mode\012\000"
	.align	2
$LC6:
	.ascii	"(3) GPIO States\012\000"
	.align	2
$LC7:
	.ascii	"GPIO: \000"
	.align	2
$LC8:
	.ascii	"wrong!\012\000"
	.text
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
	ori	$2,$2,0x804
	li	$3,16			# 0x10
	sw	$3,0($2)
$L20:
	lui	$2,%hi($LC3)
	addiu	$4,$2,%lo($LC3)
	jal	puts
	nop

	lui	$2,%hi($LC4)
	addiu	$4,$2,%lo($LC4)
	jal	puts
	nop

	lui	$2,%hi($LC5)
	addiu	$4,$2,%lo($LC5)
	jal	puts
	nop

	lui	$2,%hi($LC6)
	addiu	$4,$2,%lo($LC6)
	jal	puts
	nop

	jal	getch
	nop

	sb	$2,16($fp)
	lb	$2,16($fp)
	li	$3,50			# 0x32
	beq	$2,$3,$L16
	nop

	li	$3,51			# 0x33
	beq	$2,$3,$L17
	nop

	li	$3,49			# 0x31
	bne	$2,$3,$L21
	nop

	jal	SPI_Master_Mode
	nop

	b	$L19
	nop

$L16:
	jal	SPI_Slave_Mode
	nop

	b	$L19
	nop

$L17:
	lui	$2,%hi($LC7)
	addiu	$4,$2,%lo($LC7)
	jal	puts
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x704
	lw	$2,0($2)
	nop
	move	$4,$2
	jal	xtoa
	nop

	move	$4,$2
	jal	puts
	nop

	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	jal	puts
	nop

	b	$L19
	nop

$L21:
	lui	$2,%hi($LC8)
	addiu	$4,$2,%lo($LC8)
	jal	puts
	nop

	nop
$L19:
	b	$L20
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 7.1.0"
