 /*
 * Filename: main.c
 * Description: main program for lab 6 that uses a SPI link to write data from the gyro to the LCD.
 * Author: Clayton Tow/cctow and Joel Park/jgpark
 * Date Created: September 30, 2016
 * Last Modified by: Clayton Tow
 * Date Last Modified: October 12, 2016
 * Assignment: lab6
 * Part of: lab6
 */
#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
#include <stdlib.h>
#include <f3d_delay.h>
#include <f3d_nunchuk.h>
#include <math.h>

#define TIMER 20000
#define GRAVITY 9.81
#define AXIS 75


nunchuk_t nunchuk;

void clear_lines(int x) {
	int start;
	for(start = 10; start < 161; start++) {
		f3d_lcd_drawPixel(x, start, BLACK);
	}
}

float tilt(float accel) {
  return atan2f(accel, GRAVITY);
}
float heading(float x, float y) {
  return (180 / M_PI) * atan2f(x, y);
}
// Function to draw a rectangle
void drawRect(int x1, int x2, int y1, int y2, uint16_t color){
  int i;
  int j;
  if(x1 > x2){
    int temp = x1;
    x1 = x2;
    x2 = temp;
  }
  if(y1>y2){
    int tem = y1;
    y1 = y2;
    y2 = tem;
  }
  if (y1 > 75 && y2 > 75) {
      for(j= y2; j>= y1; j--){ 
	for (i = x1; i<=x2; i++){
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
    }
    for(j= y1; j<= y2; j++){ 
      for (i = x1; i<=x2; i++){
	f3d_lcd_drawPixel(i,j,color);
      }
    }
}

void chooseLED(int degree) {
  f3d_led_all_off();
  if (degree > 0) {
    if (degree < 50) {
      f3d_led_on(9);
    }
    else if (degree < 100) {
      f3d_led_on(10);
    }
    else if (degree < 150) {
      f3d_led_on(11);
    }
    else if (degree < 200) {
      f3d_led_on(12);
    }
    else f3d_led_on(13);
  }
  else {
    if (degree > -50) {
      f3d_led_on(9);
    }
    else if (degree > -100) {
      f3d_led_on(8);
    }
    else if (degree > -150) {
      f3d_led_on(15);
    }
    else if (degree > -200) {
      f3d_led_on(14);
    }
    else f3d_led_on(13);
  }
}
void draw(int xStart, int xEnd, int value, int prev) {
   //Draw the meter for each axis
  /*if (value >= 0 && prev >= 0 && prev >= value) {
    drawRect(xStart, xEnd, AXIS - prev, AXIS - value, WHITE);
  }
  else if (value <= 0 && prev <= 0 && prev <= value) {
    drawRect(xStart, xEnd, AXIS - prev, AXIS - value, WHITE);
  }
  else if ((value <= 0 && prev >= 0) || (value >= 0 && prev <= 0)) {
    drawRect(xStart, xEnd, AXIS, AXIS - prev, WHITE);
  }
  */
  delay(10);
  drawRect(xStart, xEnd, AXIS, AXIS - prev, WHITE);
  drawRect(xStart, xEnd, AXIS, AXIS - value, RED);
  delay(10);
}

void draw_two(int xStart, int xEnd, int value, int prev) {
   //Draw the meter for each axis
  /*if (value >= 0 && prev >= 0 && prev >= value) {
    drawRect(xStart, xEnd, AXIS - prev, AXIS - value, WHITE);
  }
  else if (value <= 0 && prev <= 0 && prev <= value) {
    drawRect(xStart, xEnd, AXIS - prev, AXIS - value, WHITE);
  }
  else if ((value <= 0 && prev >= 0) || (value >= 0 && prev <= 0)) {
    drawRect(xStart, xEnd, AXIS, AXIS - prev, WHITE);
  }
  */
  delay(10);
  drawRect(xStart, xEnd, 150, 150 - prev, WHITE);
  drawRect(xStart, xEnd, 150, 150 - value, RED);
  delay(10);
}

void accelerometer_display() {
   float fl[] = {1.1, 2.2, 3.3};
   float fl2[] = {0.0, 1.1, 2.2};
   static float xVal, yVal, zVal, xPrev, yPrev, zPrev;


   //printing
   delay(10);
   xPrev = xVal;
   yPrev = yVal;
   zPrev = zVal;

   f3d_led_all_off();
   f3d_accel_read(fl);
   xVal = tilt(fl[0]);
   yVal = tilt(fl[1]);
   zVal = tilt(fl[2]);
   delay(50);
   draw(10, 40, xVal * 400, xPrev * 400);
   draw(50, 80, yVal * 400, yPrev * 400);
   draw(90, 120, zVal * 400, zPrev * 400);
}

void nunchuk_display() {
   unsigned static short nxVal, nyVal, nzVal, nxPrev, nyPrev, nzPrev;


   //printing
   delay(10);
   nxPrev = nunchuk.ax;
   nyPrev = nunchuk.ay;
   nzPrev = nunchuk.az;
   f3d_led_all_off();
   f3d_nunchuk_read(&nunchuk);
   delay(50);
   draw_two(10, 40, nunchuk.ax / 4, nxPrev / 4);
   draw_two(50, 80, nunchuk.ay / 4, nyPrev / 4);
   draw_two(90, 120, nunchuk.az / 4, nzPrev / 4);
}


void compass_display() {
	float fl2[] = {0.0, 1.1, 2.2};
	f3d_mag_read(fl2);
    int degrees = (int)heading(fl2[0], fl2[1]);
    chooseLED(degrees);
   }

void gyro_display() {
	float test[3];
	// If you have your inits set up, this should turn your LCD screen red

	
	  clear_lines(31);
	  clear_lines(32);
	  clear_lines(33);
	  clear_lines(63);
	  clear_lines(64);
	  clear_lines(65);
	  clear_lines(95);
	  clear_lines(96);
	  clear_lines(97);
		
	  
	  f3d_gyro_getdata(test);
	  int x, y, z;
	  if(test[0] > 0) {
		for(x = 0; x < test[0]; x++) {
			if (x < 75) {
				f3d_lcd_drawPixel(31, (x * -1) + 85, GREEN);
				f3d_lcd_drawPixel(32, (x * -1) + 85, GREEN);
				f3d_lcd_drawPixel(33, (x * -1) + 85, GREEN);
			}
		}
	  } else {
		  for(x = 0; x < abs(test[0]); x++) {
			if (x < 75) {
				f3d_lcd_drawPixel(31, x + 85, GREEN);
				f3d_lcd_drawPixel(32, x + 85, GREEN);
				f3d_lcd_drawPixel(33, x + 85, GREEN);
			}
		}
	  }
	  if(test[1] > 0) {
		  for(y = 0; y < abs(test[1]); y++) {
			  if (y < 75) {
				f3d_lcd_drawPixel(63, (y * -1) + 85, RED);
				f3d_lcd_drawPixel(64, (y * -1) + 85, RED);
				f3d_lcd_drawPixel(65, (y * -1) + 85, RED);
			}
		  }	
	  } else {
		  for(y = 0; y < abs(test[1]); y++) {
			  if (y < 75) {
				f3d_lcd_drawPixel(63, y + 85, RED);
				f3d_lcd_drawPixel(64, y + 85, RED);
				f3d_lcd_drawPixel(65, y + 85, RED);
			}
		  }	
	  }
	  if(test[2] > 0) {
		  for(z = 0; z < abs(test[2]); z++) {
			  if (z < 75) {
				f3d_lcd_drawPixel(95, (z * -1) + 85, BLUE);
				f3d_lcd_drawPixel(96, (z * -1) + 85, BLUE);
				f3d_lcd_drawPixel(97, (z * -1) + 85, BLUE);
			}
		  }
	  } else {
		  for(z = 0; z < abs(test[2]); z++) {
			  if (z < 75) {
				f3d_lcd_drawPixel(95, z + 85, BLUE);
				f3d_lcd_drawPixel(96, z + 85, BLUE);
				f3d_lcd_drawPixel(97, z + 85, BLUE);
			}
		  }
	  }
}



int main(void) {

	int counter = 3;

	f3d_uart_init();
    delay(10);
    f3d_gyro_init();
    f3d_lcd_init();
    f3d_led_init();
    f3d_i2c1_init();
    delay(10);
    f3d_accel_init();
    delay(10);
    f3d_mag_init();
    delay(10);
    f3d_nunchuk_init();
    delay(10);
    
    
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  while(1) {
	  if(counter == 0) {
		  f3d_lcd_fillScreen2(BLACK);
		  f3d_lcd_drawChar(32, 0, 'x', GREEN, BLACK);
		  f3d_lcd_drawChar(64, 0, 'y', RED, BLACK);
		  f3d_lcd_drawChar(96, 0, 'z', BLUE, BLACK);
		  f3d_lcd_drawChar(0, 81, '0', YELLOW, BLACK);
		  f3d_lcd_drawChar(0, 10, '^', YELLOW, BLACK);
		  f3d_lcd_drawChar(0, 150, '_', YELLOW, BLACK);
		  int axis;
		  for (axis = 15; axis < 128; axis++) {
			  f3d_lcd_drawPixel(axis, 85, YELLOW);
			  }
		  f3d_lcd_drawString(5, 150, "gyro data", WHITE, BLACK);  
		  while(1) {
			  f3d_nunchuk_read(&nunchuk);
			  gyro_display();
			  if(nunchuk.jx > 0x85 || nunchuk.z == 0x01) {
				  counter++;
				  break;
			  }
			  else if(nunchuk.jx < 0x73 || nunchuk.c == 0x01) {
				  counter = 3;
				  break;
			  }
		  }
	 }
	 else if(counter == 1) {
		 f3d_lcd_fillScreen(WHITE);
		 f3d_lcd_drawString(5, 5, "accelerometer data", BLACK, WHITE);
		 while(1) {
			 f3d_nunchuk_read(&nunchuk);
			 accelerometer_display();
			 if(nunchuk.jx > 0x85 || nunchuk.z == 0x01) {
				  counter++;
				  break;
			  }
			  else if(nunchuk.jx < 0x73 || nunchuk.c == 0x01) {
				  counter--;
				  break;
			  }
			  delay(10);
		  }
	 }
	 else if(counter == 2) {
		 f3d_lcd_fillScreen(WHITE);
		 f3d_lcd_drawString(5, 5, "magnetometer compass data", BLACK, WHITE);
		 while(1) {
			 f3d_nunchuk_read(&nunchuk);
			 compass_display();
			 if(nunchuk.jx == 0xff || nunchuk.z == 0x01) {
				  counter++;
				  break;
			  }
			  else if(nunchuk.jx == 0x00 || nunchuk.c == 0x01) {
				  counter--;
				  break;
			  }
		  }
	 }
	 else if(counter == 3) {
		 f3d_lcd_fillScreen(WHITE);
		 f3d_lcd_drawString(5, 5, "nunchuk data", BLACK, WHITE);
		 while(1) {
			 nunchuk_display();
			 f3d_nunchuk_read(&nunchuk);
			 if(nunchuk.jx == 0xff || nunchuk.z == 0x01) {
				 counter = 0;
				 break;
			 }
			 if(nunchuk.jx == 0x00 || nunchuk.c == 0x01) {
				 counter--;
				 break;
			 }
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

/* main.c ends here */
