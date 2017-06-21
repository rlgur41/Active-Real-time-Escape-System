#include <FreeRTOS_AVR.h>

SemaphoreHandle_t sem;

int dotmatrix_way[] = {-1, 1, 2, 3}; 
/**
 * [0] = -1 : None ( myself )
 * [1] =  1 : 왼쪽 아래 ( 1 )
 * [2] =  2 : 아래 ( 2)
 * [3] =  3 : 오른쪽 아래( 3)
 */
                     
int dot_way;
int k = 0;
int table[7] = {0, 1, 2, 3, 4, 5, 6};
uint8_t data[7];
void table_iter(int fire[], int fire_size)
{
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < fire_size; j++){
      if(fire[j] == table[i]) {
         table[i] = -1;
      }
    }
  }
  for(int i = 0; i < 7; i++){
    if(table[i] != -1){
      data[i] = set_path(fire, fire_size, table[i]);
      if(i > 0){
        tx_form[k] = ZBTxRequest(addr_form[i-1], &data[i], sizeof(uint8_t));
        k++;
      }
      else{ // i == 0
        dot_way = data[i] - '0';
      }
    }
  }
}


void setup() 
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
   Serial.println("MASTER");
   Serial.println("===========Serial 9600 open===================");
   for (int thisPin = 0; thisPin < 8; thisPin++) 
   {
     pinMode(col[thisPin], OUTPUT);
     pinMode(row[thisPin], OUTPUT);
     digitalWrite(col[thisPin], HIGH);
   }

   Serial.println("Setup prepared");
   delay(1000);
}

boolean send_flag = false;
void loop()
{
  char temp[10];
  int fire[10];


    if(Serial.available()) {
        byte leng = Serial.readBytesUntil('q', temp, 10);
        Serial.print("Input data Lenght : ");
        Serial.println(leng);
    
        for(int i = 0; i < leng; i++){
          fire[i] = temp[i] -'0';
        }
        send_flag = true;
    }
    if(send_flag == true){
      Serial.println("send data !!");
      table_iter(fire, sizeof(fire) / sizeof(int));
      for(int i = 0; i < k; i++){
        data_send(tx_form[i]);
        delay(500);
      }
    }
    while(send_flag == true){
    switch(dotmatrix_way[dot_way]){
      case 1:
      LEFT_DOWN();
      break;
      case 2:
      DOWN();
      break;
      case 3:
      RIGHT_DOWN();
      break;
  }
    }
    
    delay(20);

}

