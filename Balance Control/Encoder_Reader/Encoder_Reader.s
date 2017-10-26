    .comm     counter,4,4
    .text
    .align    2
    .globl    user_interrupt
    .ent      user_interrupt
    .type	  user_interrupt, @function
user_interrupt:
    .set	  noreorder
# Beacuse other functions are called, $fp and $ra should be stored in the stack.
    addiu	  $sp, $sp, -8                  # adjust the stack, 8 bytes
    sw	      $31, 4($sp)                   # store $31 to stack[4..7]
    sw	      $fp, 0($sp)                   # store $fp to stack[0..3]
    move	  $fp, $sp                      # $fp = $sp, store $sp in $fp 
    lw		  $a0, %gp_rel(counter)($gp)	# $a0 = counter, load counter 
    jal		  xtoa				            # jump to xtoa and save position to $ra
    nop
    move 	  $a0, $v0		                # $a0 = $v0
    jal		  puts				            # jump to puts and save position to $ra
    nop
    li		  $a0, 10 		                # $a0 = 10, '\n'
    jal		  putch				            # jump to putch and save position to $ra
    nop
    ori		  $t0, $0, 255		            # $t0 = 0xff 
    li		  $t1, 0x1f800503		        # $t1 = 0x1f800503, load EXINT_CLR_REG
    sw		  $t0, 0($t1)		            # EXINT_CLR_REG = 0xff, clear all EXINT irq
    nop
    move	  $sp, $fp                      # reload $sp
    lw	      $31, 4($sp)                   # reload $ra
    lw	      $fp, 0($sp)                   # reload $fp
    addiu	  $sp, $sp, 8                   # adjust the stack
    jr		  $ra					        # jump to $ra
    nop
    .set    reorder
    .end    user_interrupt
	.size	user_interrupt, .-user_interrupt
    .align  2
    .globl  main
    .ent    main
    .type   main, @function
main:
	.set	noreorder
#   $t0 = 1
#   $t1 = register address / memory address
#   $t2 = GPIO[0] present result  
#   $t3 = GPIO[0] last result, GPIO[1] present result
#   $t4 = if ( $t2 < $t3 )
#   $v0 = counter
# Interrupt Setting
    ori     $t0, $0, 1                      # $t0 = 1
    li		$t1, 0x1f800700		            # $t1 = 0x1f800700, load SYS_CTL0_REG address
    sw	    $t0, 0($t1)		                # SYS_CTL0_REG = 1, enable system interrupt
    li		$t1, 0x1f800500		            # $t1 = 0x1f800500, load EXINT_CTL0_REG
    sw		$0,  2($t1)		                # EXINT_SET_REG = 0, set falling edge triger
    ori     $t2, $0, 4                      # $t2 = 4
    sw		$t2, 0($t1)		                # EXINT_CTL0_REG = 4, enable EXINT[2]
# GPIO setting
    li		$t1, 0x1f800704 	            # $t1 = 0x1f800704, load SYS_IOCTL_REG address
    sw		$0,  0($t1) 		            # SYS_IOCTL_REG = 0, set all GPIO input
# counter initialization
    sw		$0,  %gp_rel(counter)($gp)		# counter = 0
    lw		$v0, %gp_rel(counter)($gp)		# $v0 = counter, load counter
# Encoder reader
    # Initialize $t2, present GPIO[0] value
    lw		$t2, 2($t1)		                # $t2 = GPIO_INPUT_REG
    ori     $t2, $t2, 0x1                   # $t2 = GPIO[0]
# Check A rising signal
while:
    nop
Check_A:
    move 	$t3, $t2		                # $t3 = $t2, store last GPIO[0] value
    lw		$t2, 2($t1)		                # $t2 = GPIO_INPUT_REG
    ori     $t2, $t2, 0x1                   # $t2 = GPIO[0]
    bgt		$t2, $t3, A_Pass	            # if ($t2 > $t3), rising signal of A appears, then branch to A_Pass
    nop
    b		Check_A			                # rising signal of A not appears, branch to Check_A, continue to check
    nop
A_Pass:
    lw		$t3, 2($t1)		                # $t2 = GPIO_INPUT_REG
    ori     $t3, $t3, 0x2                   # $t2 = GPIO[1]<<1
    beqz    $t3, else                       # if ($t2 == 0), branch to else
    nop
    addiu	$v0, $v0, -1			        # $t2 == 1, negative direction, so $v0 = $v0 - 1
    b		exit_if			                # branch to exit_if
    nop
else:
    addiu	$v0, $v0, 1			            # $t2 == 0, positive direction, so $v0 = $v0 + 1
exit_if:
    sw	  	$v0, %gp_rel(counter)($gp)		# counter = $v0, store counter 
    b		while			                # branch to while
    nop
	.set	reorder
    .end    main
    .size   main, .-main
