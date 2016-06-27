#include <NewPing.h>
#include "config.h"
#include "Engine.h"
#include "TripleSonar.h"

NewPing sonar1(US_TRIGGER_PIN_1, US_ECHO_PIN_1, US_MAX_DISTANCE);
NewPing sonar2(US_TRIGGER_PIN_2, US_ECHO_PIN_2, US_MAX_DISTANCE);
NewPing sonar3(US_TRIGGER_PIN_3, US_ECHO_PIN_3, US_MAX_DISTANCE);

TripleSonar sonar(&sonar1, &sonar2, &sonar3, US_MAX_DISTANCE);

Engine engine;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // join i2c bus (address optional for master)

  sonar.setMinDistanceCm(20, 25, 20);
  sonar.setLedPinsCritical(US_LED_LEFT_CRIT, US_LED_MIDDLE_CRIT, US_LED_RIGHT_CRIT);
  sonar.setLedPinsOk(US_LED_LEFT_OK, US_LED_MIDDLE_OK, US_LED_RIGHT_OK);
  
  initLedSequence();
}

void initLedSequence()
{
  int ledOrder[] = {US_LED_LEFT_OK, US_LED_MIDDLE_OK, US_LED_RIGHT_OK, US_LED_RIGHT_CRIT, US_LED_MIDDLE_CRIT, US_LED_LEFT_CRIT};
  for (int i = 0; i <= 2; i++)
  {
    for (int j = 0; j <= 5; j++)
    {
      digitalWrite(ledOrder[j], HIGH);
      delay(100);
      digitalWrite(ledOrder[j], LOW);
    }
  }
}

void loop() {
  sonar.checkDistances();
  while(!sonar.isCritical())
  {
    engine.moveForward();
    delay(100);
    sonar.checkDistances();
  }

  engine.stop();
  delay(250);
  
  while(sonar.isCritical())
  {
    if(sonar.getBestDirection() == TS_LEFT)
    {
      engine.turnLeft();
    }
    else
    {
      engine.turnRight();
    }
    delay(100);
    sonar.checkDistances();
  }

  engine.stop();
  delay(250);
}

