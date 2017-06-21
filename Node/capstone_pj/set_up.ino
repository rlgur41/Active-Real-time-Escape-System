#include <FreeRTOS_AVR.h>


static void main_loop(void * arg)
{
    while(1) {
      data_receive(); 
      //vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L); // 500ms delay
   }
}


static void dot_matrix(void *arg)
{
  while(1){
    switch(dotmatrix_way[dot_way]){
      case 1:
      UP();
      break;
      case 4:
      LEFT();
      break;
      case 5:
      RIGHT();
      break;
      case -2:
      continue;
  }
    vTaskDelay((20L * configTICK_RATE_HZ) / 1000L); // 500ms delay
  }
}

void setup() 
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
   Serial.println("===========Serial 9600 open===================");
   for (int thisPin = 0; thisPin < 8; thisPin++) 
   {
     pinMode(col[thisPin], OUTPUT);
     pinMode(row[thisPin], OUTPUT);
     digitalWrite(col[thisPin], HIGH);
   }

  portBASE_TYPE s1, s2;   // 쓰레드 홀더

  Serial.println("===========Thread create..===================");
//  s1 = xTaskCreate(main_loop, NULL, configMINIMAL_STACK_SIZE + 150, NULL, 1, NULL); 
  Serial.println("[THREAD]receiver create success! (prioty : 1)");
//  s2 = xTaskCreate(dot_matrix, NULL, configMINIMAL_STACK_SIZE + 150, NULL, 2, NULL);
  Serial.println("[THREAD]sender create success! (prioty : 2)");
  
  Serial.println("===========Scheduler start===================");
//  vTaskStartScheduler();  // 태스크 스케쥴러 시작
//  while(1){}
}
void loop()
{

   while(1){
    data_receive(); 
    switch(dotmatrix_way[dot_way]){
      case 0:
      RIGHT_UP();
      break;
      case 2:
      RIGHT();
      break;
      case 4:
      DOWN();
      break;
      default :
      Clear();
  }
   }
}

