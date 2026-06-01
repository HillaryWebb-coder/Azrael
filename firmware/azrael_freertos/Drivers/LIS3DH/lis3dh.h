#ifndef __LIS3DH_H
#define __LIS3DH_H

#include "main.h"

#define LIS3DH_ADDR         0x19

// Registers
#define LIS3DH_WHO_AM_I     0x0F
#define LIS3DH_CTRL_REG1    0x20
#define LIS3DH_CTRL_REG2    0x21
#define LIS3DH_CTRL_REG3    0x22
#define LIS3DH_CTRL_REG4    0x23
#define LIS3DH_CTRL_REG5    0x24
#define LIS3DH_STATUS_REG   0x27
#define LIS3DH_OUT_X_L      0x28
#define LIS3DH_CLICK_CFG    0x38
#define LIS3DH_CLICK_SRC    0x39
#define LIS3DH_CLICK_THS    0x3A
#define LIS3DH_TIME_LIMIT   0x3B
#define LIS3DH_TIME_LATENCY 0x3C
#define LIS3DH_TIME_WINDOW  0x3D

// Tilt threshold in raw counts (±2g range, 16-bit: 1g ≈ 16384)
#define LIS3DH_TILT_THRESHOLD 6000  // ~sin(45°) * 16384

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LIS3DH_Data;

typedef struct {
    uint8_t tilt_x;  // 1 if tilted on X axis
    uint8_t tilt_y;  // 1 if tilted on Y axis
} LIS3DH_Tilt;

//extern osSemaphoreId_t i2cFreeSemaphoreHandle;

void lis3dh_init(void);
void lis3dh_readXYZ(LIS3DH_Data* data);
void lis3dh_getTilt(LIS3DH_Data* data, LIS3DH_Tilt* tilt);
uint8_t           lis3dh_detectTap(void);

#endif
