// Mosture sesnor functions. Reads analog values from capacitive sensor.
#include "sensors.h"

void setupMoisture(){
  pinMode(34, OUTPUT);
}

// Returns calibrated reading of sensor in RH.
float getMoisture(){
  const int air = 3440;
  const int water = 1240; // Fix me, add config!!!
  float val = analogRead(34);
  return 100 - (((val - water) * 100) / (air - water));
}

//---Todo----
//-Create calibration system
