#include  "sensors.h"

//Sensors::Sensors(unsigned long rate) : interval(rate) 
//{}

void Sensors::setup(unsigned long rate) {
  setupTemp();
}

void Sensors::loop() {
  unsigned long timePassed = millis() - lastRun;
  if (timePassed >= interval)
  {
    if (step == 1){
      convert();
      step++;
    } else if (timePassed >= interval + 2000) {
      push();
      step = 1;
      lastRun = millis();
    }
  }
}

// For sensors that require time to process.
void Sensors::convert(){
  Serial.print("converting....");
  reqTemp();
}

void Sensors::push() {
  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> doc;
  doc["st"] = getTemp();
  doc["l"] = 48.74;
  doc["f"] = 0;
  doc["m"] = getMoisture();
  char payload[50];
  serializeJson(doc, payload);
  int id = coap.put(IPAddress(192, 168, 0, 120), 5683, "sensors", payload);
  Serial.print(strlen(payload));
  Serial.print(": ");
  Serial.println(payload);
}

bool Sensors::state(){
  return running;
}

unsigned long Sensors::timeRemaining(){
  return millis () - lastRun;
}

void Sensors::setRate(unsigned long rate){
  interval = rate;
}
