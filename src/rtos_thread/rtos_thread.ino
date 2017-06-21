#include <FreeRTOS_AVR.h>

static void Thread1(void* arg) {   // receive thread
  while (1) {
    Serial.println("Thread1");
    vTaskDelay((500L * configTICK_RATE_HZ) / 1000L); // 500ms delay
  }
}

static void Thread2(void* arg) {  // send thread
  while (1) {
    Serial.println("Thread2");
    vTaskDelay((500L * configTICK_RATE_HZ) / 1000L); // 500ms delay
  }
}

void setup() {
  Serial.begin(9600);
  portBASE_TYPE s1, s2;   // 쓰레드 홀더

  s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); // Thread1 생성(run)
  s2 = xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL); // Thread2 생성(run)
  vTaskStartScheduler();  // 태스크 스케쥴러 시작
  while(1) {}
}

void loop() {} // 사용하지 않음

