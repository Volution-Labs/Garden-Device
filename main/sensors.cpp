#include  "sensors.h"

//Sensors::Sensors(unsigned long rate) : interval(rate) 
//{}

void Sensors::setup(unsigned long rate) {
  //setupTemp();
  setRate(rate);
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
  Serial.print("converting.... ");
  reqTemp();
}

void Sensors::push() {
  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> doc;
  doc["st"] = getTemp();
  doc["l"] = 48.74;
  doc["f"] = flowPulse;
  flowPulse = 0;
  doc["m"] = getMoisture();
  char payload[50];
  serializeJson(doc, payload);
  int id = coap.put(serverAddress, 5683, "sensors", payload);
  // Send: ip, port, route, coapType, method, token, tokenLen, payload, payloadLen, contentType
  //int id = coap.send(serverAddress, 5683, "sensors", COAP_CON, COAP_POST, (uint8_t)223, (uint8_t)3, (uint8_t *)payload, (uint32_t)2, COAP_APPLICATION_JSON)
  Serial.print("Sensor Data: ");
  Serial.print(payload);
}
// IPAddress&, int, const char [8], COAP_TYPE, COAP_METHOD,    NULL,     int, uint8_t*,    size_t, COAP_CONTENT_TYPE
// IPAddress , int, char,           COAP_TYPE, COAP_METHOD, uint8_t, uint8_t,  uint8_t, uint32_t , COAP_CONTENT_TYPE
bool Sensors::state(){
  return running;
}

unsigned long Sensors::timeRemaining(){
  return millis () - lastRun;
}

void Sensors::setRate(unsigned long rate){
  interval = rate;
}
