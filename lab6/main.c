/* main.c ---
*
* Filename: main.c
* Description:
* Author: Joel Park, Yongming Fan 
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
  f3d_uart_init();
  f3d_gyro_init();

  

  // If you have your inits set up, this should turn your LCD screen red
  f3d_lcd_init();
  f3d_lcd_fillScreen(BLACK);
  f3d_lcd_drawChar(36, 77, 'x', GREEN, BLACK);
  f3d_lcd_drawChar(66, 77, 'y', GREEN, BLACK);
  f3d_lcd_drawChar(96, 77, 'z', GREEN, BLACK);
  int l = 0;
  while (l < 125){
    f3d_lcd_drawPixel(l, 75, WHITE);
    l ++;
  }

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  float data[3];

  while (1){
    f3d_gyro_getdata(data);
    int i = 0;
    int j = 0;
    int k = 0;
    //data[0]
    if (data[0] >= 0){
      while (i <= data[0] && i <= 75 && i >= 0){
	f3d_lcd_drawPixel(34, 75 - i, GREEN);//x
	i ++;
      }
    }
    else if (data[0] < 0){
      while (i >= data[0] && i >= -75 && i <= 0){
	f3d_lcd_drawPixel(34, 75 - i, GREEN);//x
	i --;
      }
    }

    if (data[1] >= 0){
      while (j <= data[1] && j <= 75 && j >= 0){
	f3d_lcd_drawPixel(64, 75 - j, GREEN);//x
	j ++;
      }
    }
    else if (data[1] < 0){
      while (j >= data[1] && j >= -75 && j <= 0){
	f3d_lcd_drawPixel(64, 75 - j, GREEN);//x
	j --;
      }
    }
    
    if (data[2] >= 0){
      while (k <= data[2] && k <= 75 && k >= 0){
	f3d_lcd_drawPixel(94, 75 - k, GREEN);//x
	k ++;
      }
    }
    else if (data[2] < 0){
      while (k >= data[2] && k >= -75 && k <= 0){
	f3d_lcd_drawPixel(94, 75 - k, GREEN);//x
	k --;
      }
    }

    char x[5];
    char y[5];
    char z[5];
    
    snprintf(x, 5, "%f", data[0]);
    snprintf(y, 5, "%f", data[1]);
    snprintf(z, 5, "%f", data[2]);

    f3d_lcd_drawString(36, 90, x, GREEN, BLACK);
    f3d_lcd_drawString(66, 90, y, GREEN, BLACK);
    f3d_lcd_drawString(96, 90, z, GREEN, BLACK);
    
    f3d_gyro_getdata(data);
    i = 0;
    j = 0;
    k = 0;
    while (i <= 75){
      f3d_lcd_drawPixel(34, i, BLACK);//x
      f3d_lcd_drawPixel(34, 150 - i, BLACK);//x
      i ++;
    }
    while (j <= 75){
      f3d_lcd_drawPixel(64, j, BLACK);//y
      f3d_lcd_drawPixel(64, 150 - j, BLACK);//y
      j ++;
    }
    while (k <= 75){
      f3d_lcd_drawPixel(94, k, BLACK);//y
      f3d_lcd_drawPixel(94, 150 - k, BLACK);//y
      k ++;
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

/* main.c ends here */
