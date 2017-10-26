#################################################################
# TITLE: uart0 library
# AUTHOR: Astro
# DATE CREATED: 2017-10-25
# FILENAME: uart0.s
# PROJECT: Balance Control System
# COPYRIGHT: FDU
# REGISTER USAGE: $v0, $v1, $a0, $ra
# DESCRIPTION:
#   There are two functions in this library.
#   They are listed in uart0.h
#   uart0_write: Send a byte via uart0.
#   uart0_read: read a byte from uart0.
#################################################################
    .text
    .align    2
    .globl    uart0_write
    .ent      uart0_write
    .type     uart0_write, @function
####################################
# This is uart0_write entrance.
####################################
uart0_write:
    .set      noreorder
    li    $v0, 0x1f800000           # load UART0_READ_REG
uart0_waite:                        # check if uart0 is busy
    lw    $v1, 1($v0)               # $v1 = UART0_BUSY_REG
    bgtz  $v1, uart0_waite          # branch to uart0_waite if $v1 == 1
    nop
    sb    $a0, 2($v0)               # send
    jr    $ra                       # jump to $ra
    nop
    .set      reorder
    .end      uart0_write
    .size     uart0_write, .-uart0_write
    .align    2
    .globl    uart0_read
    .ent      uart0_read
    .type     uart0_read, @function
###################################
# This is uart0_read entrance.
###################################
uart0_read:
    .set      noreorder
    li    $v0, 0x1f800000           # load UART0_READ_REG
uart0_rdy_waite:                    # check if uart0 data is ready
    lw    $v1, 5($v0)               # $v1 = UART0_DATA_RDY_REG    
    beqz  $v1, uart0_rdy_waite
    nop
    lw    $v1, 0($v0)               # $v0 = UART0_READ_REG, read data
    move  $v0, $v1
    jr    $ra                       # jump to $ra
    nop
    .set      reorder
    .end      uart0_read
    .size     uart0_read, .-uart0_read
