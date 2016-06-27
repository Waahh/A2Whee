#include "Arduino.h"
#include "Engine.h"

Engine::Engine()
{
  _i2cAddress = I2C_DEFAULT_ADDRESS;
}

Engine::Engine(uint8_t i2cAddress)
{
  _i2cAddress = i2cAddress;
}

void Engine::setI2CAddress(uint8_t i2cAddress)
{
  _i2cAddress = i2cAddress;
}

void Engine::moveForward()
{
  Serial.println("Moving forward");
  changeMotorState(DIRECTION_FORWARD, 50, 50);
}

void Engine::moveBackward()
{
  Serial.println("Moving backward");
  changeMotorState(DIRECTION_BACKWARD, 50, 50);
}

void Engine::turnLeft()
{
  Serial.println("Turning left");
  changeMotorState(DIRECTION_LEFT, 35, 35);
}

void Engine::turnRight()
{
  Serial.println("Turning right");
  changeMotorState(DIRECTION_RIGHT, 35, 35);
}

void Engine::stop()
{
  Serial.println("Stopping");
  changeMotorState(DIRECTION_FORWARD, 0, 0);
}

void Engine::changeMotorState(unsigned char motorDirection, unsigned char motorSpeedA , unsigned char motorSpeedB)
{
  setMotorSpeedAB(motorSpeedA, motorSpeedB);
  delay(10); // required delay
  setMotorDirection(motorDirection);
}

void Engine::setMotorSpeedAB(unsigned char motorSpeedA , unsigned char motorSpeedB)
{
  motorSpeedA=map(motorSpeedA,0,100,0,255);
  motorSpeedB=map(motorSpeedB,0,100,0,255);
  
  sendCommand(I2C_HEADER_MOTORSPEED, motorSpeedA, motorSpeedB);
}

void Engine::setMotorPWMFrequence(unsigned char pwmFrequence)
{    
  sendCommand(I2C_HEADER_PWM_FREQUENCE, pwmFrequence, I2C_BYTE_NOTHING);
}

void Engine::setMotorDirection(unsigned char motorDirection)
{     
  sendCommand(I2C_HEADER_DIRECTION, motorDirection, I2C_BYTE_NOTHING);
}

void Engine::sendCommand(uint8_t header, uint8_t byteA, uint8_t byteB)
{
  if(ENGINE_DEBUG)
  {
    return;
  }
  
  Wire.beginTransmission(_i2cAddress);  // transmit to device
  Wire.write(header);                   // direction control header
  Wire.write(byteA);                    // send control information
  Wire.write(byteB);                    // send control information  
  Wire.endTransmission();               // stop transmitting 
  
}

