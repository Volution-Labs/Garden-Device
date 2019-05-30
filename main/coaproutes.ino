// Routes and handlers for coap communication. Uses coap-simple.h
// Respond: ip, port, messageid, msg, msglen, code, type, token, tokenlen

void setupCOAPRoutes() {
  coap.response(handle_coap_response);
  coap.server(handle_coap_water, "water");
  coap.server(handle_coap_config, "config/server");
  coap.server(handle_coap_config, "config/rate");
}

void handle_coap_water(CoapPacket &packet, IPAddress ip, int port) {
  // Parse payload
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  unsigned long time;
  time = atoi(p);

  Serial.println(String(time));
  if (time >= 1000  && time <= 4200000) {
    // start water
    valve.on(time);
    coap.sendResponse(ip, port, packet.messageid, "ok", 2, COAP_CONTENT, COAP_TEXT_PLAIN, packet.token, 4);
  } else {
    // out of range.
    coap.sendResponse(ip, port, packet.messageid, "err: time out of range", 22, COAP_BAD_OPTION, COAP_TEXT_PLAIN, packet.token, 4);
  }
}

void handle_coap_config(CoapPacket &packet, IPAddress ip, int port) {
  // +++++Function Rewrite+++++
  // parse: second resorce = group, payload = key get(valve = valve)
  // if get
    // begin group from second resorce
    // get and return value from given key
    // if no key return err
  // if put
    // begin group from second resorce
    // check if pref exsists return err if not.
    // set new valve to key.
    
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  const int capacity = JSON_OBJECT_SIZE(1);
  StaticJsonDocument<capacity> doc;
  DeserializationError err = deserializeJson(doc, p);
  
  if (doc.containsKey("serverIP")) {
    Serial.println(p);
    Serial.println("server ip: ");
    const char* newIP = doc["serverIP"];
    Serial.println(newIP);
  }
}

void handle_coap_response(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Coap Response got]");

  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  Serial.println(p);
}
 
