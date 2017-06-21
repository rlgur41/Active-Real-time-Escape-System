#include <XBee.h>

XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse();

void setup () {
  delay(1000);
  Serial.begin(9600);
  xbee.begin(Serial);
  Serial.println("starting up yo!");
}

void loop () {

  // 1. This will read any data that is available:
  xbee.readPacket();

  // 2. Now, to check if a packet was received: 
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(zbRx);
    
     Serial.println("=============================");
     for (int i = 0; i < zbRx.getDataLength(); i++) {
         Serial.println(char(zbRx.getData(i)));
     }
     Serial.println("\n=============================");
    }
  }
}
