#include <XBee.h>

XBee xbee = XBee();



// node-2-1 
int dotmatrix_way[] = { 0, -1, 2, -1, 4 }; 
//node 1-1
//int dotmatrix_way[] = { -1, 1, -1, -1, 4, 5, -1 };
//node 2-3
//int dotmatrix_way[] = { 0, -1, 2, -1, -1, -1, 6 };
//node 1-3
//int dotmatrix_way[] = {-1, -1, -1, 3, -1, 5, 6 };
//node 2-2
//int dotmatrix_way[] = {0, 1, -1, 3, -1, 5, -1 }; 
//node 1-2
//int dotmatrix_way[] = { -1, -1, 2, -1, 4, 5, 6};
int dot_way = -2;

volatile boolean retry = true;
XBeeAddress64 master = XBeeAddress64(0x0013a200, 0x415B660E); // master
XBeeAddress64 _2_3_node = XBeeAddress64(0x0013a200, 0x415B6631);
XBeeAddress64 _1_3_node = XBeeAddress64(0x0013a200, 0x415B667A);
XBeeAddress64 _2_2_node = XBeeAddress64(0x0013a200, 0x415B663E);
XBeeAddress64 _1_2_node = XBeeAddress64(0x0013a200, 0x415B660F);
XBeeAddress64 _2_1_node = XBeeAddress64(0x0013a200, 0x415B6612);
XBeeAddress64 _1_1_node = XBeeAddress64(0x0013a200, 0x415B663D);

ZBRxResponse zbRx = ZBRxResponse(); 
ZBTxStatusResponse txStatus = ZBTxStatusResponse();
XBeeResponse response = XBeeResponse();
ModemStatusResponse msr = ModemStatusResponse();

void data_send(ZBTxRequest& zbTx)
{ 
  while(retry == true){
      xbee.send(zbTx);
      
      if (xbee.readPacket(500)) {

        // should be a znet tx status              
        if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
          xbee.getResponse().getZBTxStatusResponse(txStatus);

          // get the delivery status, the fifth byte
          if (txStatus.getDeliveryStatus() == SUCCESS) {
              // success.  time to celebrate
              Serial.println("[OK] Send Success");
              retry = false;
          } else {
        // the remote XBee did not receive our packet. is it powered on?
              Serial.println("[FAIL] Send Fail");
              retry = true;
          }
        }
     } 
    else {
    // local XBee did not provide a timely TX Status Response -- should not happen
        Serial.println("FAIL] Unknown Error");
    }
  }
}
void data_receive()
{
  xbee.readPacket(); // data read
    
    if (xbee.getResponse().isAvailable()) {
      // buffer에 데이터가 들어왔는데
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        // Receive 신호다
        
        // 받은 신호의 데이터를 zbRx에 적재
        xbee.getResponse().getZBRxResponse(zbRx);
       
        if (zbRx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
            // 보낸곳으로부터 ACK이 날라옴
            Serial.println("[OK] Ack send successfully");
        } else {
            Serial.println("[FAIL] Ack doesn't send successfully"); // 상대방이 받지 못함.
        }
        Serial.println("=============================");
        for (int i = 0; i < zbRx.getDataLength(); i++) {  //decode uint8_t to char
            Serial.write("data : ");
            Serial.write(char(zbRx.getData(i))); // 데이터 출력
            dot_way = char(zbRx.getData(i)) - '0';
        }
     
        Serial.println("\n=============================");
      } 
      else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) { // Device on/off 유무
        xbee.getResponse().getModemStatusResponse(msr);
        if (msr.getStatus() == ASSOCIATED) {
          Serial.println("[OK] msr state ASSOCIATE");
        } else if (msr.getStatus() == DISASSOCIATED) {
          Serial.println("[FAIL] DISASSOCIATED");
        } else {
          Serial.println("[Unknown] Associated error");
        }
      } else {
        Serial.println("[Unknown] Not expecting");    
        dot_way = -2;
      }
    } else if (xbee.getResponse().isError()) {
      Serial.println("[FAIL] ERROR");
      dot_way = -2;
    }
 
}
