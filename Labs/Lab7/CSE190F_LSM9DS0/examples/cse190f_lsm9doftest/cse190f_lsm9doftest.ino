/*
*  Simple Test Code for the IMU LSM9D0
*  University of California, San Diego
*  Jorge Garza (jgarzagu@ucsd.edu).
*/ 
#include <Wire.h>
#include <SPI.h>

// lsm9d0 Address
#define LSM9DS0_ACC_ADR  (0x3D >> 1)
#define LSM9DS0_GYRO_ADR (0xD5 >> 1)
#define LSM9DS0_MAG_ADR  (0x3D >> 1)

// lsm9d0 Registers
#define LSM9DS0_REGISTER_WHO_AM_I_XM        0x0F
#define LSM9DS0_REGISTER_WHO_AM_I_G         0x0F
#define LSM9DS0_XM_ID                      (0b01001001)
#define LSM9DS0_G_ID                       (0b11010100)

// lsm9d0 Orientation
#define ACC_ORIENTATION(X, Y, Z)  {imu.accADC[ROLL]  = -X; imu.accADC[PITCH]  = -Y; imu.accADC[YAW]  = Z;}
#define GYRO_ORIENTATION(X, Y, Z) {imu.gyroADC[PITCH] = -X; imu.gyroADC[ROLL] = Y; imu.gyroADC[YAW] = -Z;}
#define MAG_ORIENTATION(X, Y, Z)  {imu.magADC[ROLL]  =  -X; imu.magADC[PITCH]  =  -Y; imu.magADC[YAW]  = Z;}

// Global Vars
uint8_t rawADC[6];

typedef struct {
  int16_t  magADC[3];
  int16_t  gyroADC[3];
  int16_t  accADC[3];
} imu_t;
imu_t imu;

enum rc {
  ROLL,
  PITCH,
  YAW
};

void setup() 
{
  uint8_t id;
  boolean chip_detected = true;
  
  Serial.begin(9600);
  Serial.println("LSM9D0 Test");
  
  //I2C init
  Wire.begin();
  
  // Detect the IMU chip
  id = i2c_readReg(LSM9DS0_ACC_ADR, LSM9DS0_REGISTER_WHO_AM_I_XM);
  if (id != LSM9DS0_XM_ID) chip_detected = false;
  id = i2c_readReg(LSM9DS0_GYRO_ADR, LSM9DS0_REGISTER_WHO_AM_I_G);
  if (id != LSM9DS0_G_ID) chip_detected = false;
    
  if (!chip_detected) {
    Serial.println("Unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  
  // Initialize Acc, Gyro & Mag
  ACC_init ();
  Gyro_init();
  Mag_init();
  
}

void loop() 
{
  ACC_getADC ();
  Serial.print("Accel X: "); Serial.print((int)imu.accADC[ROLL]);
  Serial.print(" Y: "); Serial.print((int)imu.accADC[PITCH]);       
  Serial.print(" Z: "); Serial.print((int)imu.accADC[YAW]);
  Gyro_getADC();
  Serial.print("\t Gyro X: "); Serial.print((int)imu.gyroADC[PITCH]);   
  Serial.print(" Y: "); Serial.print((int)imu.gyroADC[ROLL]);        
  Serial.print(" Z: "); Serial.print((int)imu.gyroADC[YAW]); 
  Device_Mag_getADC();
  Serial.print("\t Mag X: "); Serial.print((int)imu.magADC[ROLL]);     
  Serial.print(" Y: "); Serial.print((int)imu.magADC[PITCH]);         
  Serial.print(" Z: "); Serial.print((int)imu.magADC[YAW]);
  Serial.println("");  
  
  delay(200);
}

// *** Acc/Gyro/Mag functions ***
void ACC_init () {
  i2c_writeReg(LSM9DS0_ACC_ADR,0x20,0x57);   // 50Hz data rate, XYZ enable
  i2c_writeReg(LSM9DS0_ACC_ADR,0x21,0x00);   // Set scale to 2g
}

void ACC_getADC () {   
  i2c_getSixRawADC(LSM9DS0_ACC_ADR, 0x28 | 0x80);

  ACC_ORIENTATION( ((rawADC[1]<<8) | rawADC[0])>>4 ,
                  ((rawADC[3]<<8) | rawADC[2])>>4 ,
                  ((rawADC[5]<<8) | rawADC[4])>>4 );
}

void Gyro_init(){
  i2c_writeReg(LSM9DS0_GYRO_ADR, 0x20, 0x0F);   //Ctrl reg 1: 100Hz, normal power, XYZ enable
  i2c_writeReg(LSM9DS0_GYRO_ADR, 0x23, 0x30);   //2000 dps scale
}

void Gyro_getADC(){
  i2c_getSixRawADC(LSM9DS0_GYRO_ADR, 0x28 | 0x80);
  GYRO_ORIENTATION( ((rawADC[1]<<8) | rawADC[0]) ,
                    ((rawADC[3]<<8) | rawADC[2]) ,
                    ((rawADC[5]<<8) | rawADC[4]) );
}

void Mag_init() {
  i2c_writeReg(LSM9DS0_MAG_ADR,0x24,0x08);  // [CTRL_REG5_XM] Mag data rate - 12.5 Hz
  i2c_writeReg(LSM9DS0_MAG_ADR,0x25,0x00);  // [CTRL_REG6_XM] Mag scale to +/- 2Ga
  i2c_writeReg(LSM9DS0_MAG_ADR,0x26,0x00);  // [CTRL_REG7_XM] Continous conversion mode
  i2c_writeReg(LSM9DS0_MAG_ADR,0x23,0x04);  // [CTRL_REG4_XM]
  i2c_writeReg(LSM9DS0_MAG_ADR,0x12,0x09);  // [INT_CTRL_REG_M]
}

void Device_Mag_getADC() {
  i2c_getSixRawADC(LSM9DS0_MAG_ADR,0x08 | 0x80);
  MAG_ORIENTATION( ((rawADC[1]<<8) | rawADC[0]) ,
                   ((rawADC[3]<<8) | rawADC[2]) ,
                   ((rawADC[5]<<8) | rawADC[4]) );
}


// *** I2C Transmission functions ***

void i2c_writeReg(byte address, byte reg, byte value)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission(); 
}

byte i2c_readReg(byte address, byte reg)
{
  uint8_t value;
  i2c_read_reg_to_buf(address, reg, &value, 1);
  return value;
}

void i2c_getSixRawADC(uint8_t address, uint8_t reg) {
  i2c_read_reg_to_buf(address, reg, rawADC, 6);
}

byte i2c_read_reg_to_buf(byte address, byte reg, uint8_t *buffer, byte len)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)len);

  // Wait around until enough data is available
  while (Wire.available() < len);

  for (uint8_t i=0; i<len; i++) {
    buffer[i] = Wire.read();
  }
  Wire.endTransmission();

  return len;
}
