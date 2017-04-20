/************************
 *f3d_led.c
 * contains intializations/functions for the leds
 * Functions by Patrick Gibbons and Joel Park, framework by Geoffrey Brown(?)
 * Date Created: ?
 * Last Modified: 09/09/16
 * Lab3
 * Lab3 - sequenceLED
 ************************/

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>


//intializes the port and pins for the leds on the board
void f3d_led_init(void) {
  GPIO_InitTypeDef GPIO_LED;
  GPIO_StructInit(&GPIO_LED);
  GPIO_LED.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_LED.GPIO_OType = GPIO_OType_PP;
  GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_LED);
}

/*Turns on the appropriate led as specified by the parameter.*/
void f3d_led_on(int led) {
  switch (led) {
  case 0: GPIOE->BSRR = GPIO_Pin_9;
    break;
  case 1: GPIOE->BSRR = GPIO_Pin_10;
    break;
  case 2: GPIOE->BSRR = GPIO_Pin_11;
    break;
  case 3: GPIOE->BSRR = GPIO_Pin_12;
    break;
  case 4: GPIOE->BSRR = GPIO_Pin_13;
    break;
  case 5: GPIOE->BSRR = GPIO_Pin_14;
    break;
  case 6: GPIOE->BSRR = GPIO_Pin_15;
    break;
  case 7: GPIOE->BSRR = GPIO_Pin_8;
    break;
  }
}

/*Turns off the approiate led as specified by the parameter*/ 
void f3d_led_off(int led) {
  switch (led) {
  case 0: GPIOE->BRR = GPIO_Pin_9;
    break;
  case 1: GPIOE->BRR = GPIO_Pin_10;
    break;
  case 2: GPIOE->BRR = GPIO_Pin_11;
    break;
  case 3: GPIOE->BRR = GPIO_Pin_12;
    break;
  case 4: GPIOE->BRR = GPIO_Pin_13;
    break;
  case 5: GPIOE->BRR = GPIO_Pin_14;
    break;
  case 6: GPIOE->BRR = GPIO_Pin_15;
    break;
  case 7: GPIOE->BRR = GPIO_Pin_8;
    break;
  }
} 

/*Turns on all LEDs*/
void f3d_led_all_on(void) {
  GPIOE->BSRR = GPIO_Pin_8;
  GPIOE->BSRR = GPIO_Pin_9;
  GPIOE->BSRR = GPIO_Pin_10;
  GPIOE->BSRR = GPIO_Pin_11;
  GPIOE->BSRR = GPIO_Pin_12;
  GPIOE->BSRR = GPIO_Pin_13;
  GPIOE->BSRR = GPIO_Pin_14;
  GPIOE->BSRR = GPIO_Pin_15;
} 

/*Turns off all LEDs*/
void f3d_led_all_off(void) {
  GPIOE->BRR = GPIO_Pin_8;
  GPIOE->BRR = GPIO_Pin_9;
  GPIOE->BRR = GPIO_Pin_10;
  GPIOE->BRR = GPIO_Pin_11;
  GPIOE->BRR = GPIO_Pin_12;
  GPIOE->BRR = GPIO_Pin_13;
  GPIOE->BRR = GPIO_Pin_14;
  GPIOE->BRR = GPIO_Pin_15;
} 

/* led.c ends here */

