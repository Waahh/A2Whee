#ifndef Engine_h
#define Engine_h

#include "Arduino.h"
#include <Wire.h>

#define I2C_HEADER_MOTORSPEED     0x82
#define I2C_HEADER_PWM_FREQUENCE  0x84
#define I2C_HEADER_DIRECTION      0xaa
#define I2C_BYTE_NOTHING          0x01

//#define MotorSetA                 0xa1
//#define MotorSetB                 0xa5

#define DIRECTION_FORWARD         0b0101
#define DIRECTION_BACKWARD        0b1010
#define DIRECTION_LEFT            0b0110
#define DIRECTION_RIGHT           0b1001

#define I2C_DEFAULT_ADDRESS       0x0f   // Set the default address of the I2CMotorDriver

#ifndef ENGINE_DEBUG
#define ENGINE_DEBUG              false
#endif

class Engine
{
  public:
    Engine();
    Engine(uint8_t i2cAddress);
    
    void setI2CAddress(uint8_t i2cAddress);
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stop();

  private:
    uint8_t _i2cAddress;
    
    void setMotorSpeedAB(unsigned char motorSpeedA , unsigned char motorSpeedB);
    void setMotorPWMFrequence(unsigned char pwmFrequence);
    void setMotorDirection(unsigned char motorDirection);
    void sendCommand(uint8_t header, uint8_t byteA, uint8_t byteB);
};
#endif
