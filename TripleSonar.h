#ifndef TripleSonar_h
#define TripleSonar_h

#include "Arduino.h"
#include <NewPing.h>

#define TS_LEFT   0
#define TS_MIDDLE 1
#define TS_RIGHT  2


class TripleSonar
{
  public:
    TripleSonar(NewPing *sonar1, NewPing *sonar2, NewPing *sonar3, int maxDistanceCm);
    void checkDistances();
    void setMinDistanceCm(int left, int middle, int right);
    void setLedPinsCritical(int left, int middle, int right);
    void setLedPinsOk(int left, int middle, int right);
    bool isCritical();
    int getBestDirection();
    
  private:  
    NewPing* _sonar[3];
    
    int _maxDistanceCm;
    int _minDistanceCm[3];
    
    int _ledPinsOk[3];
    bool _ledPinsOkSet = false;
    int _ledPinsCritical[3];
    bool _ledPinsCriticalSet = false;
    
    int _lastMeasuredDistance[3];
    bool _criticalDistance[3];

    void _initLeds(int leds[]);
};
#endif
