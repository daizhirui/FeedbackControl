  .comm	    half_T,4,4
  .text
    .align  2
    .globl  user_interrupt
    .ent    user_interrupt
user_interrupt:
    .set    noreorder
    .set    noat
  nop
  lw		$t0, %gp_rel(half_T)($gp)	# $t0 = half_T 
  addi	    $t0, $t0, 1 			    # $t0 = $t0 + 20
  sw		$t0, %gp_rel(half_T)($gp)	# half_T = $t0 
  ori		$t0, $0, 255		        # $t0 = 0xff 
  li		$t1, 0x1f800503		        # $t1 = 0x1f800503, load EXINT_CLR_REG
  sw		$t0, 0($t1)		            # EXINT_CLR_REG = 0xff, clear all EXINT irq
  jr		$ra					        # jump to $ra
  nop
    .set    reorder
    .set    at
    .end    user_interrupt
    .align  2
    .globl  main
    .ent    main
    .type   main, @function
main:
    .set    noreorder
    .set    noat
#   $v0 = for counter
#   $t0 = 1
#   $t1 = register address / memory address
#   $v1 = pwm_half_T
  nop
  ori       $t0, $0, 1                  # $t0 = 1
  li		$t1, 0x1f800700		        # $t1 = 0x1f800700, load SYS_CTL0_REG address
  sw		$t0, 0($t1)		            # SYS_CTL0_REG = 1, enable system interrupt
  li		$t1, 0x1f800500		        # $t1 = 0x1f800500, load EXINT_CTL0_REG
  sw		$0,  2($t1)		            # EXINT_SET_REG = 0, set falling edge triger
  ori       $t2, $0, 2                  # $t2 = 2
  sw		$t2, 0($t1)		            # EXINT_CTL0_REG = 2, enable EXINT[1]
  li		$t1, 0x1f800704 	        # $t1 = 0x1f800704, load SYS_IOCTL_REG address
  sw		$t0, 0($t1) 		        # SYS_IOCTL_REG = 1, set GPIO[0] output
  ori       $t2, $0, 1                  # $t2 = 1
  sw		$t2, %gp_rel(half_T)($gp)   # half_T = 1
while:
  sw		$t0, 1($t1) 		        # GPIO_OUTPUT_REG = 1, set GPIO[0] high
  lw		$v0, %gp_rel(half_T)($gp)   # $v0 = half_T, half_T is a global varible 
#  move      $v0, $v1                   # $v0 = $v1, initialize the counter
for0:
  addi	    $v0, $v0, -1		        # $v0 = $v0 - 1, decrease for counter
  bgtz      $v0, for0                   # if ($v0>0), branch to for0
  nop
  sw		$0,  1($t1)		            # GPIO_OUTPUT_REG = 1, set GPIO[0] low 
  lw		$v0, %gp_rel(half_T)($gp)   # $v0 = half_T, half_T is a global varible 
for1:
  addi	    $v0, $v0, -1		        # $v0 = $v0 - 1, decrease for counter
  bgtz      $v0, for1                   # if ($v0>0), branch to for1
  nop
  b		    while			            # jump to while
  nop
    .set    reorder
    .set    at
    .end    main
    .size   main, .-main
  