/* main.c ---
*
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_led.h>///////////////////////////////
#include <stdio.h>
#include <math.h>

#define TIMER 20000

int AXIS = 75;

int BOOSTER = 750;

   
float xprev = 0.0;
float yprev = 0.0;
float zprev = 0.0;

void delayy(void) {
  int i = 500000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}
//Function to draw a rectangle
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


void accelDraw(float alpx,float alpy,float alpz, float xp, float yp, float zp){
    float xPrev = xp*BOOSTER;
    float yPrev = yp*BOOSTER;
    float zPrev = zp*BOOSTER;
    float xValue = alpx *BOOSTER;
    float yValue = alpy*BOOSTER;
    float zValue = alpz*BOOSTER;

    //Draw the X-value meter
    drawRect(10, 40, AXIS, AXIS - xValue, RED);
    delayy();
    if (xValue >= 0 && xPrev >= 0 && xPrev >= xValue) {
      drawRect(10, 40, AXIS - xPrev, AXIS - xValue, WHITE);
    }
    else if (xValue <= 0 && xPrev <= 0 && xPrev <= xValue) {
      drawRect(10, 40, AXIS - xPrev, AXIS - xValue, WHITE);
    }
    else if (xValue <= 0 && xPrev >= 0) {
      drawRect(10, 40, AXIS, AXIS - xPrev, WHITE);
    }
    else if (xValue >= 0 && xPrev <= 0) {
      drawRect(10, 40, AXIS, AXIS - xPrev, WHITE);
    }

    //Draw the Y-value meter
    drawRect(50, 80, AXIS, AXIS - yValue, GREEN);
    delayy();
    if (yValue >= 0 && yPrev >= 0 && yPrev >= yValue) {
      drawRect(50, 80, AXIS - yPrev, AXIS - yValue, WHITE);
    }
    else if (yValue <= 0 && yPrev <= 0 && yPrev <= yValue) {
      drawRect(50, 80, AXIS - yPrev, AXIS - yValue, WHITE);
    }
    else if (yValue <= 0 && yPrev >= 0) {
      drawRect(50, 80, AXIS, AXIS - yPrev, WHITE);
    }
    else if (yValue >= 0 && yPrev <= 0) {
      drawRect(50, 80, AXIS, AXIS - yPrev, WHITE);
    }
    //Draw the Z-value meter
    drawRect(90, 120, AXIS, AXIS - zValue, BLUE);
    delayy();
    if (zValue >= 0 && zPrev >= 0 && zPrev >= zValue) {
      drawRect(90, 120, AXIS - zPrev, AXIS - zValue, WHITE);
    }
    else if (zValue <= 0 && zPrev <= 0 && zPrev <= zValue) {
      drawRect(90, 120, AXIS - zPrev, AXIS - zValue, WHITE);
    }
    else if (zValue <= 0 && zPrev >= 0) {
      drawRect(90, 120, AXIS, AXIS - zPrev, WHITE);
    }
    else if (zValue >= 0 && zPrev <= 0) {
      drawRect(90, 120, AXIS, AXIS - zPrev, WHITE);
    }
  
}



int main(void) {


  f3d_led_init(); //initializes led
  f3d_user_btn_init(); //initializes button

   f3d_uart_init();  

   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);


   f3d_lcd_init();

  // Set up your inits before you go ahead
   //  while(1){
   //  printf("howdy");
   //} This works but theres problems elsewhere
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);





  float magArray[3] = {1.1, 2.2, 3.3};

  float accelArray[4] = {1.1,2.2,3.3,4.4};
  
  float A = 0.00;
  float g = 9.81;
  
  
  //Turn screen white, and draw a line for the axis
  f3d_lcd_fillScreen(WHITE);
  drawRect(0, 1000, AXIS, AXIS, BLACK);

  while(1){    

    if(user_btn_read()== 0){
    
    //printf("acceldata\n");
    f3d_accel_read(accelArray);
   float  AX = accelArray[0];
   float AY = accelArray[1];
   float AZ = accelArray[2];

   float alphaX = atan2f(AX,g); //tilt angle

   float alphaY = atan2f(AY,g);
    
   float alphaZ = atan2f(AZ,g);
   char tx[5];
   char ty[5];
   char tz[5];
   snprintf(tx,5, "%f", alphaX);
   snprintf(ty,5, "%f", alphaY);
   snprintf(tz,5, "%f", alphaZ);
   
   f3d_lcd_drawString(10, 0, tx, BLACK, WHITE);
   f3d_lcd_drawString(50, 0, ty, BLACK, WHITE);
   f3d_lcd_drawString(90, 0, tz, BLACK, WHITE);
   
   accelDraw(alphaX, alphaY, alphaZ, xprev, yprev, zprev);
   xprev = alphaX;
   yprev = alphaY;
   zprev = alphaZ;
   
   float heading = atan2f(magArray[1],magArray[0]); //compass
    }//end of if

    else{

      f3d_mag_read(magArray);
       
      float heading = atan2f(magArray[1],magArray[0]);
       
       float dir = heading*(180.0/3.141592654);
       int light = 8; //8 - 16

       if(dir<=22.5 && dir >=-22.5){
	 light = 13;
       }
       else if(dir>=22.5 && dir<=67.5){
	 light = 12;
       }
       else if(dir>=67.5 && dir<=112.5){
	 light = 11;
       }
       else if(dir>=112.5 && dir <= 157.5){
	 light =10;
       }
       else if(dir>= 157.5 || dir <= -157.5){
	 light =9;
       }
       else if(dir>= -157.5 && dir <=-112.5){
	 light =8;
       }
       else if(dir>=-112.5 && dir <= -67.5){
	 light=15;
       }
       else if(dir>=-67.5 && dir <=-22.5){
	 light =14;
       }
       delay(10);
       f3d_led_all_off();
       f3d_led_on(light);
       printf("%f\n",dir);


    }//end of else


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

