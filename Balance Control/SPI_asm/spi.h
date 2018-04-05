/* ------------------------------------------------------------
 * File Name: spi.h
 * Author: Astro
 * Description: function definition
 * ------------------------------------------------------------ */
/**
 * @brief setup the mode of spi
 * 
 * @param mode >=1: master, 0: slave
 */
void spi_mode_set(int mode);
/**
 * @brief send a byte, for master
 * 
 * @param value data to send
 */
void spi_master_write(unsigned char value);
/**
 * @brief send a byte, for slave
 * 
 * @param value data to send
 */
void spi_slave_write(unsigned char value);
/**
 * @brief read a byte
 * 
 * @return unsigned char 
 */
unsigned char spi_read();
#define SPI_CTL_REG 0x1f800d04
#define spi_cs_on()     *(volatile unsigned long *)(SPI_CTL_REG)=0x6    // for master only
#define spi_cs_off()    *(volatile unsigned long *)(SPI_CTL_REG)=0x4    // for master only