#include "valve.h"

Valve::Valve(byte attachTo) : pin(attachTo) 
{
  pinMode(pin, OUTPUT);
  pinMode(5, OUTPUT);
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
  digitalWrite(5, HIGH); // Visual State Display
}

void Valve::off(){
  digitalWrite(pin, LOW);
  digitalWrite(5, LOW); // Visual State Display
  open = false;
}

bool Valve::state(){
  return open;
}

unsigned long Valve::timeRemaining(){
  return millis () - startTime;
}
