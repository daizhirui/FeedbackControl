  .text
    .align 2
    .globl  user_interrupt
    .ent    user_interrupt
    .type   user_interrupt, @function
user_interrupt:
    .set    noreorder
    .set    noat
  addi	$s2, $s2, 1			# $s2 = $s2 + 1, pwm_half_T++.
  ori		$t0, $0, 255		# $t0 = 0xff
  sw		$t0, 3($s4) 		# store $t0 to EXINT_CLR_REG, clear EXINT irq.
  jr		$31					# jump to $31
    .set    reorder
    .end    user_interrupt
    .size   user_interrupt, .-user_interrupt
    .align  2
    .globl  main
    .ent    main
    .type   main, @function
main:
    .set    noreorder
    .set    noat
  nop
  ori       $s1, $0, 0x1        # $s1 = 1.
  li		$s0, 0x1f800704		# $s0 =0x1f800704, load SYS_IOCTL_REG address.
  sw		$s1, 0($s0)		    # write 0x1 to SYS_IOCTL_REG, set GPIO[0] OUTPUT. 
  ori       $s2, $0, 20          # $s2 = 20, store pwm_half_T
while:
  sw		$s1, 1($s0)		    # write 0x1 to GPIO_OUTPUT_REG, set GPIO[0] high.
  move		$s3, $s2		    # $s3 = pwm_half_T, as a counter.
for0:
  addi	    $s3, $s3, -1		# $s3 = s3 -1, decrement loop counter.
  bgtz      $s3, for0            # if ($s2>0), branch to for
  nop
  sw		$0, 1($s0)		    # write 0 to GPIO_OUTPUT_REG, set GPIO[0] low.
  move		$s3, $s2		    # $s3 = pwm_half_T, as a counter. 
for1:
  addi	    $s3, $s3, -1		# $s3 = $3 -1, decrement loop counter.
  bgtz      $s3, for1            # if ($s3>0), branch to for
  nop
  b		    while			    # branch to while
  nop
    .set    reorder
    .end    main
    .size   main, .-main
