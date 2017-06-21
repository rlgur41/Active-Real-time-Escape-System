/*void send_message(XBeeAddress64 addr_list, uint8_t data)
{
  ZBTxRequest dest = ZBTxRequest(addr_list, data, sizeof(data));
  xbee.send(dest);
}

uint8_t* read_message()
{
  uint8_t* ret;
  ZBRxResponse zbRx = ZBRxResponse();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(zbRx);
      ret = (uint8_t*)malloc(zbRx.getDataLength());

      for(int i = 0; i < zbRx.getDataLength(); i++){
        ret[i] = char(zbRx.getData(i));
        Serial.print("data : ");
        Serial.print(ret[i]);
      }
    }
  }
  Serial.println();
  return ret;
}
*/
