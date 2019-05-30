#include "valve.h"

Valve::Valve(byte attachTo) : pin(attachTo) 
{
  pinMode(pin, OUTPUT);
}

void Valve::setup() {
  
}
void Valve::loop() {
  if (open && millis () - startTime >= interval)
  {
    off();
  }
}

void Valve::on(unsigned long time) {
  interval = time;
  open = true;
  startTime = millis();
  digitalWrite(pin, HIGH);
}

void Valve::off(){
  digitalWrite(pin, LOW);
  open = false;
}

bool Valve::state(){
  return open;
}

unsigned long Valve::timeRemaining(){
  return millis () - startTime;
}
