#ifndef sensors_h
#define sensors_h
 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <coap-simple.h>

// Define Sensor functions
// Todo: Use namespaces
void setupMoisture();
float getMoisture();
void setupTemp();
void reqTemp();
float getTemp();
void setupLight();
void displaySensorDetails();
void configureSensor();
void printLight();
extern Coap coap;

class Sensors {
  private:
    bool running = false;
    int step = 1;
    unsigned long lastRun;
    unsigned long interval = 10000;
  public:
    //Sensors(unsigned long rate);
    void getData();
    bool state();
    unsigned long timeRemaining();
    void setup(unsigned long rate);
    void setRate(unsigned long rate);
    void loop();
    void push();
    void convert();
};

#endif
