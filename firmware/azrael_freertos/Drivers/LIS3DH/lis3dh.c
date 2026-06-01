#include "lis3dh.h"
#include "i2c.h"

// Helper: write one register
static void lis3dh_writeReg(uint8_t reg, uint8_t val){
    uint8_t buf[2] = {reg, val};
    I2C_Start();
    I2C_Write(LIS3DH_ADDR, buf, sizeof(buf));
    I2C_Stop();
}

// Helper: read one register
static void lis3dh_readReg(uint8_t reg, uint8_t* val, uint16_t size){
    I2C_Start();
    I2C_Write(LIS3DH_ADDR, &reg, 1);
    I2C_Start();
    I2C_Read(LIS3DH_ADDR, val, size);
    I2C_Stop();
}

void lis3dh_init(void){
    uint8_t id;

    // Verify chip identity
    lis3dh_readReg(LIS3DH_WHO_AM_I, &id, 1);
    if(id != 0x33) return;  // wrong device

    // CTRL_REG1: 100Hz, normal mode, XYZ enabled
    // ODR = 0101 (100Hz), LPen=0, Zen=Yen=Xen=1
    lis3dh_writeReg(LIS3DH_CTRL_REG1, 0x57);

    // CTRL_REG4: ±2g, high resolution, BDU enabled
    // BDU=1, FS=00 (±2g), HR=1
    lis3dh_writeReg(LIS3DH_CTRL_REG4, 0x88);

    // CTRL_REG3: route click interrupt to INT1
    lis3dh_writeReg(LIS3DH_CTRL_REG3, 0x80);

    // Click config: single tap on X, Y, Z
    lis3dh_writeReg(LIS3DH_CLICK_CFG, 0x15);

    // Click threshold: ~1g  (value = threshold / (2 * full_scale / 128))
    lis3dh_writeReg(LIS3DH_CLICK_THS, 0x30);

    // Time limit: how long click pulse can be (~50ms at 100Hz)
    lis3dh_writeReg(LIS3DH_TIME_LIMIT, 0x05);

    // Time latency: dead time after click (~100ms)
    lis3dh_writeReg(LIS3DH_TIME_LATENCY, 0x0A);
}

void lis3dh_readXYZ(LIS3DH_Data* data){
    uint8_t reg = LIS3DH_OUT_X_L | 0x80;  // 0x80 = auto-increment flag
    uint8_t raw[6];

//    osSemaphoreAcquire(i2cFreeSemaphoreHandle, osWaitForever);
    lis3dh_readReg(reg, raw, 6);
//    osSemaphoreAcquire(i2cFreeSemaphoreHandle, osWaitForever);

    // Combine bytes — LIS3DH is little-endian, left-justified in 16-bit
    data->x = (int16_t)((raw[1] << 8) | raw[0]);
    data->y = (int16_t)((raw[3] << 8) | raw[2]);
    data->z = (int16_t)((raw[5] << 8) | raw[4]);
}

void lis3dh_getTilt(LIS3DH_Data* data, LIS3DH_Tilt* tilt){
    lis3dh_readXYZ(data);

    // Tilt detected when axis exceeds ~45 degrees from vertical
    int16_t ax = data->x;
    int16_t ay = data->y;

     if(ax > LIS3DH_TILT_THRESHOLD){
    	 tilt->tilt_x = ax > 0 ? 1 : -1;
    }else {
    	tilt->tilt_x = 0;
    }

    if(ay > LIS3DH_TILT_THRESHOLD){
    	tilt->tilt_y = ay > 0 ? 1 : -1;
    } else {
    	tilt->tilt_y = 0;
    }
}

uint8_t lis3dh_detectTap(void){
    uint8_t click_src;
    lis3dh_readReg(LIS3DH_CLICK_SRC, &click_src, 1);
    // Bit 6 (IA) = interrupt active, Bit 4 (Sign) direction, bits 2:0 = axis
    return (click_src & 0x40) ? 1 : 0;
}
