// Mosture sesnor functions. Reads analog values from capacitive sensor.
#include "sensors.h"

void setupMoisture(){
  pinMode(34, OUTPUT);
}

// Returns calibrated reading of sensor in RH.
float getMoisture(){
  const int air = 3440;
  const int water = 0; // Fix me!!!
  float val;
  val = analogRead(34);
  return val;
}

//---Todo----
//-Create calibration system
