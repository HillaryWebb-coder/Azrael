#include "i2c.h"
#include "stm32f103xb.h"

void I2C_Init(void) {
    // Initialize I2C peripheral (e.g., I2C1)
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN); // Enable I2C1 clock and GPIOB clock

    // Configure PB6 (SCL) and PB7 (SDA) as alternate function open-drain
    GPIOB->CRL |= (GPIO_CRL_CNF6 | GPIO_CRL_MODE6) | (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOB->ODR |= (1 << 6) | (1 << 7); // Set PB6 and PB7 high (open-drain)

    I2C1->CR1 |= I2C_CR1_SWRST; // Reset I2C1
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = 36; // APB1 clock frequency in MHz (e.g., 36 MHz)
    I2C1->CCR = 180; // Configure for 100 kHz I2C speed (CCR = Fpclk1 / (2 * I2C_speed))
    I2C1->TRISE = 37; // Maximum rise time for 100 kHz (TRISE = Fpclk1 / 1,000,000 + 1)
    I2C1->CR1 |= I2C_CR1_PE; // Enable I2C1
}

void I2C_Start(void) {
    // Enable ACK
    I2C1->CR1 |= I2C_CR1_ACK;
    // Generate START condition
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait for START condition generated
}

void I2C_Write(uint8_t address, uint8_t *data, uint8_t size) {
    I2C1->DR = (address << 1) | 0; // Send slave address with write bit
    while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent
    uint8_t temp = I2C1->SR1 | I2C1->SR2; // Clear ADDR flag by reading SR1 and SR2

    while(size){
        // Wait for TXE set
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = *data++; // Send byte
        while (!(I2C1->SR1 & I2C_SR1_BTF)); // Wait for byte transfer finished
        size--;
    }
}

void I2C_Stop(void) {
    // Generate STOP condition
    I2C1->CR1 |= I2C_CR1_STOP;
}


void I2C_Read(uint8_t address, uint8_t* data, uint16_t size) {
    if (size == 0) return;

    if(size == 1) {
        I2C1->DR = (address << 1) | 1; // Send slave address with read bit
        while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent

        I2C1->CR1 &= ~I2C_CR1_ACK; // Disable ACK for last byte
        uint8_t temp = I2C1->SR1 | I2C1->SR2; // Clear ADDR flag
        I2C1->CR1 |= I2C_CR1_STOP; // Generate STOP condition
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        *data = I2C1->DR; // Read last byte
    } else {
        I2C1->DR = (address << 1) | 1; // Send slave address with read bit
        while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent
        uint8_t temp = I2C1->SR1 | I2C1->SR2; // Clear ADDR flag

        while(size > 2) {
            while (!(I2C1->SR1 & I2C_SR1_RXNE));
            *data++ = I2C1->DR; // Read byte
            I2C1->CR1 |= I2C_CR1_ACK; // Enable ACK for next byte
            size--;
        }

        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        *data++ = I2C1->DR; // Read second to last byte
        I2C1->CR1 &= ~I2C_CR1_ACK; // Disable ACK for last byte
        I2C1->CR1 |= I2C_CR1_STOP; // Generate STOP condition
        size--;
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        *data = I2C1->DR; // Read last byte
        size--;
    }
}


    
