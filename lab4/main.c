//Joel Park and Caleb Gardner
/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author:
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}


int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  //Initializations for word count
  int wordCount = 1;
  int lineCount = 1;
  int charCount = 0;
  
  int c;

  while (1){
   // putstring("hello"); currently commented out to avoid confusing word count output
   
    //printf("hello world");
    while((c = getchar()) != 0x1b){
      putchar(c);
        charCount++;

        if (c == '\n') {
                lineCount+=1;}
        if (c == ' ' || c == '\n') {
                wordCount++;
	}
    }
    printf("%d words, %d lines, %d chars", wordCount, lineCount, charCount);
    
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

