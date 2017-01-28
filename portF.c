/*
 * File						: portF.c
 * Description		: The hardware operations specific to port(F) are performed here
 *
 * Author : ALEXANDER     
 * Date		: January 5, 2016 
 */ 
 
#include "portF.h"

void PortF_Init(void){ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}

/* BUTTON PRESS CHECK
=====================
		unsigned long In;  // input from PF4
		In = GPIO_PORTF_DATA_R&0x10; // read PF4 into In
    if(In == 0x00){              // zero means SW1 is pressed
*/

/* LIGHT ON
===========
	  GPIO_PORTF_DATA_R = 0x04;    // LED is blue
    Delay();                     // wait 0.1 sec
    return SUCCESS;
	
// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
*/
