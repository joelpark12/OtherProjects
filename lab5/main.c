/**********************************************************  
 *   Author: Andrew Messer(ajmesser), Joel Park(jgpark)  
 *   Date Created: 9/28/16
 *   Last Modified by: Andrew Messer and Joel Park
 *   Date Last Modified: 8/28/16
 *   Assignment: Lab 5
 */ 



//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>


void delay(void) {
  int i = 600000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void){
  int axis = 0;

  f3d_gyro_init();
  f3d_uart_init();
  user_btn_init();
  f3d_led_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  float array[3] = {1.6, 3.7, 5.8};
  while(1) {
    f3d_gyro_getdata(array);
   
    delay();
   
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET) {
      int  c = USART_ReceiveData(USART1);
   
      if (c == 'x') {
	axis = 0;
      }

      if (c == 'y') {
	 axis = 1;
      }

       if (c == 'z') {
	 axis = 2;
      }
    }

    if (user_btn_read() == 1) { 
      if (axis == 2) {
	axis = 0;
      }
      else {
	axis++;
      }
    }
     printf("%f\n", array[axis]);

    if (array[axis] > 5) {
      f3d_led_on(1);
      delay();
    }
    else {
      f3d_led_off(1);
    }
    if (array[axis] > 95) {
      f3d_led_on(2);
      delay();
    }
    else {
      f3d_led_off(2);
    }
    if (array[axis] > 185) {
       f3d_led_on(3);
      delay();
     }
     else {
      f3d_led_off(3);
    }
     if (array[axis] > 275) {
	f3d_led_on(4);
      delay();
      }
     else {
       f3d_led_off(4);
    }
     if (array[axis] > 360) {
       f3d_led_on(5);
       delay();
     }
     else {
       f3d_led_off(5);
    }
     if (array[axis] < -5) {
       f3d_led_on(0);
       delay();
     }
     else {
       f3d_led_off(0);
     } 
     if (array[axis] < -120) {
	 f3d_led_on(7);
	 delay();
       }
       else {
	 f3d_led_off(7);
       } 
       if (array[axis] < -245) {
	 f3d_led_on(6);
	 delay();
       }
       else {
	 f3d_led_off(6);
       } 
       
       if (array[axis] < -360) {
	 f3d_led_on(5);
	 delay();
       }
       else {
	 f3d_led_off(5);
       }
  }
}
  
    
  

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}

