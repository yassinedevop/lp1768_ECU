#pragma import(__use_no_semihosting_swi)

#include "serial.h"
#include "timer.h"
#include "LPC17xx.h"

#include <stdio.h> // semi-hosting needs retargeting

extern void retarget_init(); // see retartget.c

#define LED1  (1<<18) 
#define LED2  (1<<20)
#define LED3  (1<<21)
#define LED4  (1<<23)

void delay(uint32_t ms)
{
  SysTick->LOAD = SystemCoreClock*ms/100;
  SysTick->VAL = 0;
  SysTick->CTRL = 0x5;
  while((SysTick->CTRL & 0x10000 ) == 0);

  SysTick->CTRL = 0;
}

int main(void)
{
  SysTick_Config(SystemCoreClock/10);
    retarget_init();
   LPC_GPIO1->FIODIR |= LED1|LED2|LED3|LED4; //CMSIS definitions
   LPC_GPIO1->FIOPIN ^= LED1;

   printf("Clock is initialized\n\r");

   do {
      LPC_GPIO1->FIOPIN ^= LED2|LED3;
      delay(1000);
   } while(1);
   return 0;
}
