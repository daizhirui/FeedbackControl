#################################################################
# TITLE: spi library
# AUTHOR: Astro
# DATE CREATED: 2017-10-25
# FILENAME: spi.s
# PROJECT: Balance Control System
# COPYRIGHT: FDU
# REGISTER USAGE: $v0, $v1, $a0, $ra
# EXTERNAL REGISTER USAGE:
#   U1_CTL0_REG         0x1f800804
#   SPI_READ_REG        0x1f800d00
#   SPI_BUSY_REG        0x1f800d01
#   SPI_WRITE_REG       0x1f800d02
#   SPI_IRQACK_REG      0x1f800d03
#   SPI_CTL_REG         0x1f800d04
#   SPI_DATA_RDY_REG    0x1f800d05
# DESCRIPTION:
#   There are 3 functions in this library.
#   They are listed in spi.h
#   spi_mode_set: setup spi mode.
#   spi_master_write: send a byte as a master.
#   spi_read: read a byte from spi.
#################################################################
    .text
    .align    2
    .globl    spi_mode_set
    .ent      spi_mode_set
    .type     spi_mode_set, @function
####################################
# This is spi_mode_set entrance.
####################################
spi_mode_set:
# $a0 = 0, set spi slave; otherwise, set spi master.
    .set      noreorder
    li    $v0, 0x1f800804               # load U1_CTL0_REG address
    ori   $v1, $0, 0x10                 # $v1 = 0x10
    sh    $v1, 0($v0)                   # U1_CTL0_REG = 0x10, uart1 disable
    li    $v0, 0x1f800d00               # load SPI_READ_REG address
    beqz  $a0, set_slave                # branch to set_slave if $a0 == 0
    nop
set_master:
    ori   $v1, $0, 0x4                  # $v1 = 4
    sb    $v1, 4($v0)                   # SPI_CTL_REG = 0x4, SPI master enable, cs disable
    b     exit_spi_mode_set             # branch to exit_spi_mode_set
    nop
set_slave:
    sb    $0,  4($v0)                   # SPI_CTL_REG = 0x0, SPI slave enable
exit_spi_mode_set:
    li    $v1, 0x6                      # $v1 = 6
    sb    $v1, 3($v0)                   # SPI_IRQACK_REG = 0x6, clear SPI irq
    jr    $ra                           # jump to $ra
    nop
    .set      reorder
    .end      spi_mode_set
    .size     spi_mode_set, .-spi_mode_set
    .align    2
    .globl    spi_master_write
    .ent      spi_master_write
    .type     spi_master_write, @function
####################################
# This is spi_write entrance.
####################################
spi_master_write:
    .set      noreorder
    li    $v0, 0x1f800d00               # load SPI_READ_REG address
    ori   $v1, $0, 0x6                  # Sv1 = 6
    sb    $v1, 4($v0)                   # SPI_CTL_REG = 0x6, SPI master enable, cs enable
    sb    $v1, 3($v0)                   # SPI_IRQACK_REG = 0x6, clear SPI irq
spi_waite_0:
    lw    $v1, 1($v0)                   # $v1 = SPI_BUSY_REG, check if SPI is busy
    bgtz  $v1, spi_waite_0              # brach to spi_waite_0 if ($v1 > 0)
    nop
    sb    $a0, 2($v0)                   # SPI_WRITE_REG = $a0, send the data
spi_waite_1:
    lw    $v1, 1($v0)                   # $v1 = SPI_BUSY_REG, check if SPI is busy
    bgtz  $v1, spi_waite_1              # brach to spi_waite_1 if ($v1 > 0)
    ori   $v1, $0, 0x4                  # $v1 = 0x4
#    sb    $v1, 4($v0)                   # SPI_CTL_REG = 0x4, cs off, release slave
#    sb    $v1, 3($v0)                   # SPI_IRQACK_REG = 0x4, clear SPI irq
    jr    $ra                           # jump to $ra
    nop
    .set      reorder
    .end      spi_master_write
    .size     spi_master_write, .-spi_master_write
####################################
# This is spi_slave_write entrance.
# slave will not wait after a byte is writen in to SPI_WRITE_REG.
####################################
    .align    2
    .globl    spi_slave_write
    .ent      spi_slave_write
    .type     spi_slave_write, @function
spi_slave_write:
    .set      noreorder
    li    $v0, 0x1f800d00               # load SPI_READ_REG address
    ori   $v1, $0, 0x6                  # Sv1 = 6
    sb    $v1, 3($v0)                   # SPI_IRQACK_REG = 0x6, clear SPI irq
spi_waite_2:
    lw    $v1, 1($v0)                   # $v1 = SPI_BUSY_REG, check if SPI is busy
    bgtz  $v1, spi_waite_2              # brach to spi_waite_2 if ($v1 > 0)
    nop
    sb    $a0, 2($v0)                   # SPI_WRITE_REG = $a0, send the data
spi_waite_3:
    lw    $v1, 1($v0)                   # $v1 = SPI_BUSY_REG, check if SPI is busy
    bgtz  $v1, spi_waite_3              # brach to spi_waite_3 if ($v1 > 0)
    ori   $v1, $0, 0x4                  # $v1 = 0x4
    sb    $v1, 3($v0)                   # SPI_IRQACK_REG = 0x4, clear SPI irq
    jr    $ra                           # jump to $ra
    nop
    .set      reorder
    .end      spi_slave_write
    .size     spi_slave_write, .-spi_slave_write
    .align    2
    .globl    spi_read
    .ent      spi_read
    .type     spi_read, @function
####################################
# This is spi_read entrance.
####################################
spi_read:
    .set      noreorder
    li    $v0, 0x1f800d00               # load SPI_READ_REG address
    ori   $v1, $0, 0x10                 # $v1 = 0x10
    sb    $v1, 3($v0)                   # SPI_IRQACK_REG = 0x10, clear SPI irq
spi_rdy_waite:
    lw    $v1, 5($v0)                   # $v1 = SPI_DATA_RDY_REG,check if SPI data is ready
    beqz  $v1, spi_rdy_waite            # branch to spi_rdy_waite if ($v1 == 0)
    nop
    lw    $v0, 0($v0)                   # $v0 = SPI_READ_REG, read and store SPI data
    jr    $ra                           # jump to $ra
    nop
    .set      reorder
    .end      spi_read
    .size     spi_read, .-spi_read
