// Lab4.c
// Runs on TM4C123
// Program written by: put your names here
// Date Created: 
// Last Modified:  
// Lab number: 5
// Brief description of the program
//  
// Hardware connections


#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);

int main(void){   
	PLL_Init();          // bus clock at 80 MHz
	DAC_Init();
	Piano_Init(); 
	Sound_Init(0); 
	EnableInterrupts();

	
  while(1){                

	WaitForInterrupt();		
		
  }             
}


