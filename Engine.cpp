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
  setMotorSpeedAB(50,45);
  delay(10); //this delay needed
  setMotorDirection(DIRECTION_FORWARD);
}

void Engine::moveBackward()
{
  Serial.println("Moving backward");
  setMotorSpeedAB(50,50);
  delay(10); //this delay needed
  setMotorDirection(DIRECTION_BACKWARD);
}

void Engine::turnLeft()
{
  Serial.println("Turning left");
  setMotorSpeedAB(35,35);
  delay(10); //this delay needed
  setMotorDirection(DIRECTION_LEFT);
}

void Engine::turnRight()
{
  Serial.println("Turning right");
  setMotorSpeedAB(35,35);
  delay(10); //this delay needed
  setMotorDirection(DIRECTION_RIGHT);
}

void Engine::stop()
{
  Serial.println("Stopping");
  setMotorSpeedAB(0,0);
  delay(10); //this delay needed
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

