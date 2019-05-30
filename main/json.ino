void mk_sensor_payload(){
  const int capacity = JSON_OBJECT_SIZE(3);
  StaticJsonDocument<capacity> doc;
  doc["soil-temp"] = 42;
  doc["valve"] = 48.748010;
  doc["device"] = "main";
  char payload[128];
  serializeJson(doc, payload);
  Serial.println(payload);
}
