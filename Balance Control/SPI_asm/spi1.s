    .text
    .align  2
    .globl  master
    .ent    master
master:
    .set    noreorder
    li		$v0, 0x1f800804     # $v0 = 0x1f800804
    li		$v1, 0x10           # $v1 =0x10
    sw		$v1, 0($v0)         # UART1_CTL = 0x10
    li		$v0, 0x1f800d00     # $v0 = 0x1f800d00
    li		$v1, 0x6            # $v1 = 0x6
    sw      $v1, 4($v0)         # SPI_CTL = 0x6
    sw      $v1, 3($v0)         # SPI_CLR = 0x6
loop:
    li      $t0, 'A'            # $v0 = 'A'
    li      $v0, 0x1f800d00
    sw      $v1, 3($v0)         # SPI_CLR = 0x6
spi_wait:
    lw      $t1, 1($v0)         # $t1 = SPI_BUSY
    bgtz    $t1, spi_wait
    nop
    sw      $t0, 2($v0)         # SPI_WRITE = 'A'
spi_rdy:
    lw      $t1, 5($v0)         # $t1 = SPI_DATA_READY
    beqz    $t1, spi_rdy
    nop
    lw      $a0, 0($v0)         # $a0 = SPI_READ
    jal     xtoa
    nop
    move    $a0, $v0
    jal     puts
    nop
    j       loop
    nop
    .set    reorder
    .end    master

    .align  2
    .globl  slave
    .ent    slave
slave:
    .set    noreorder
    li		$v0, 0x1f800804     # $v0 = 0x1f800804
    li		$v1, 0x10           # $v1 =0x10
    sw		$v1, 0($v0)         # UART1_CTL = 0x10
    li		$v0, 0x1f800d00     # $v0 = 0x1f800d00
    sw      $0,  4($v0)         # SPI_CTL = 0x0
    sw      $v1, 3($v0)         # SPI_CLR = 0x10
    li      $t0, 'B'            # $t0 = 'B'
spi_wait_:
    lw      $t1, 1($v0)         # $t1 = SPI_BUSY
    bgtz    $t1, spi_wait_
    nop
    sw      $t0, 2($v0)         # SPI_WRITE = 'B'
loop_:
    li      $v0, 0x1f800d00
spi_rdy_:
    lw      $t1, 5($v0)         # $t1 = SPI_DATA_READY
    beqz    $t1, spi_rdy_
    nop
    sw      $v1, 3($v0)         # SPI_CLR = 0x10
    sw      $t0, 2($v0)         # SPI_WRITE = 'B'
    j       loop_
    nop
    .set    reorder
    .end    slave
