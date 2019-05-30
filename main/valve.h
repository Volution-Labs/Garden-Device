#ifndef valve_h
#define valve_h
 
#include <Arduino.h>

class Valve {
  private:
    const byte pin;
    bool open = false;
    unsigned long startTime;
    unsigned long interval = 60000;
  public:
    Valve(byte attachTo);
    bool state();
    unsigned long timeRemaining();
    void setup();
    void loop();
    void on(unsigned long time);
    void off();
    
};

#endif
