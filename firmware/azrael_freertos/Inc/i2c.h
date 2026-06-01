# ifndef I2C_H
# define I2C_H

#include "stm32f1xx.h"

// I2C function declarations
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t address, uint8_t *data, uint8_t size);
void I2C_Read(uint8_t address, uint8_t* data, uint16_t size);

#endif // I2C_H