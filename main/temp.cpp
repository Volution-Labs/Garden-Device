// DS18B20 soil prob functions.
#include <OneWire.h>
#include "config.h"
#include "sensors.h"
#include <DallasTemperature.h>

OneWire oneWire(TEMP_PIN);
DallasTemperature oneWireTemp(&oneWire);
  
void tempSetup() {
  // Get device address and test, if no device address or test fail, get and store new address.
  oneWireTemp.begin();
}

void reqTemp(){
  oneWireTemp.requestTemperatures();
}

float getTemp() {
  return oneWireTemp.getTempCByIndex(0);
}
