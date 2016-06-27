#include "Arduino.h"
#include <NewPing.h>
#include "TripleSonar.h"

TripleSonar::TripleSonar(NewPing *sonar1, NewPing *sonar2, NewPing *sonar3, int maxDistanceCm)
{
  _sonar[TS_LEFT] = sonar1;
  _sonar[TS_MIDDLE] = sonar2;
  _sonar[TS_RIGHT] = sonar3;
  _maxDistanceCm = maxDistanceCm;
}

void TripleSonar::setMinDistanceCm(int left, int middle, int right)
{
  _minDistanceCm[TS_LEFT] = left;
  _minDistanceCm[TS_MIDDLE] = middle;
  _minDistanceCm[TS_RIGHT] = right;
}

void TripleSonar::setLedPinsCritical(int left, int middle, int right)
{
  _ledPinsCritical[TS_LEFT] = left;
  _ledPinsCritical[TS_MIDDLE] = middle;
  _ledPinsCritical[TS_RIGHT] = right;
  _initLeds(_ledPinsCritical);
  _ledPinsCriticalSet = true;
}

void TripleSonar::setLedPinsOk(int left, int middle, int right)
{
  _ledPinsOk[TS_LEFT] = left;
  _ledPinsOk[TS_MIDDLE] = middle;
  _ledPinsOk[TS_RIGHT] = right;
  _initLeds(_ledPinsOk);
  _ledPinsOkSet = true;
}

void TripleSonar::_initLeds(int leds[])
{
  for(int i = 0; i <= 2; i++)
    pinMode(leds[i], OUTPUT);
}

void TripleSonar::checkDistances()
{
  for (int i = 0; i <= 2; i++)
  {
    int distance = _sonar[i]->ping();
    if(distance == 0)
    {
      distance = _maxDistanceCm * US_ROUNDTRIP_CM;
    }
    _lastMeasuredDistance[i] = distance;
    if(distance < _minDistanceCm[i] * US_ROUNDTRIP_CM)
    {
      _criticalDistance[i] = true;
      digitalWrite(_ledPinsCritical[i], HIGH);
    }
    else
    {
      _criticalDistance[i] = false;
      digitalWrite(_ledPinsCritical[i], LOW);
    }
  }
  int maxDist = max(_lastMeasuredDistance[TS_LEFT], max (_lastMeasuredDistance[TS_MIDDLE], _lastMeasuredDistance[TS_RIGHT]));
  for(int i = 0; i <= 2; i++)
  {
    if(_lastMeasuredDistance[i] == maxDist)
    {
      digitalWrite(_ledPinsOk[i], HIGH);
    }
    else
    {
      digitalWrite(_ledPinsOk[i], LOW);
    }
  }
}

bool TripleSonar::isCritical()
{
  return _criticalDistance[TS_LEFT] || _criticalDistance[TS_MIDDLE] || _criticalDistance[TS_RIGHT];
}

int TripleSonar::getBestDirection()
{
  return _lastMeasuredDistance[TS_LEFT] > _lastMeasuredDistance[TS_RIGHT] ? TS_LEFT : TS_RIGHT;
}


