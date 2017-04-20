#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

//Joel Park and Patrick Gibbons

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_led_init();
  f3d_user_btn_init();
  f3d_led_all_off();
  while(1) {
    int i;
    for(i = 0; i <= 7; i++) {
      if(user_btn_read() == 0) {
	f3d_led_on(i);
	delay();
	f3d_led_off(i);
	if(i == 7) {
	  f3d_led_all_on();
	  delay();
	  f3d_led_all_off();
	} 
      } else {
	delay();
	i--;
      }
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

// part 3.3
/* int main(void) {
  /* GPIO_InitTypeDef GPIO_LED; */
  /* GPIO_InitTypeDef GPIO_BUTTON; */
  /* GPIO_StructInit(&GPIO_LED); */
  /* GPIO_LED.GPIO_Pin = GPIO_Pin_9;  */
  /* GPIO_LED.GPIO_Mode = GPIO_Mode_OUT; */
  /* GPIO_LED.GPIO_OType = GPIO_OType_PP; */
  /* GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz; */
  /* GPIO_LED.GPIO_PuPd = GPIO_PuPd_NOPULL; */
  /* RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE); */
  /* GPIO_Init(GPIOE, &GPIO_LED); */
  /* GPIO_StructInit(&GPIO_BUTTON); */
  /* GPIO_BUTTON.GPIO_Pin = GPIO_Pin_0; */
  /* GPIO_BUTTON.GPIO_Mode = GPIO_Mode_IN; */
  /* GPIO_BUTTON.GPIO_PuPd = GPIO_PuPd_NOPULL; */
  /* RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); */
  /* GPIO_Init(GPIOA, &GPIO_BUTTON); */
  /* GPIOE->BRR = GPIO_Pin_9; */
  /* while(1) { */
    /* if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) != 0) { */
    /*   GPIOE->BSRR = GPIO_Pin_9; */
    /* } else { */
    /*   GPIOE->BRR = GPIO_Pin_9; */
    /* } */
  /* } */
/* } */

/* main.c ends here */
