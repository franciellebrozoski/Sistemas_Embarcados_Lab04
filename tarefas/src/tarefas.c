#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

typedef struct{
  uint8_t led_num;
  uint32_t tempo;
} LED;


void thread(void *arg){
  uint8_t state = 0;
  uint32_t tick;
  LED *aux = (LED *) arg;
  
  while(1){
    tick = osKernelGetTickCount();
    
    state ^= aux->led_num;
    LEDWrite(aux->led_num, state);
    
    osDelayUntil(tick + (*aux).tempo);
  } // while
} // thread2

void main(void){
  
  LEDInit(LED4|LED3|LED2|LED1);
  
  LED qual_led1, qual_led2, qual_led3, qual_led4;
  qual_led1.led_num = LED1;
  qual_led1.tempo = 200;
  qual_led2.led_num = LED2;
  qual_led2.tempo = 300;
  qual_led3.led_num = LED3;
  qual_led3.tempo = 500;
  qual_led4.led_num = LED4;
  qual_led4.tempo = 700;
  
  osKernelInitialize();
  
  thread1_id = osThreadNew(thread2, &qual_led1, NULL);
  thread2_id = osThreadNew(thread2, &qual_led2, NULL);
  thread3_id = osThreadNew(thread2, &qual_led3, NULL);
  thread4_id = osThreadNew(thread2, &qual_led4, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
