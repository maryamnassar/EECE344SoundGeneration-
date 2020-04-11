// Lab4.c
// Runs on TM4C123
// Program written by: Maryam Nassar 
// Date Created: March 27, 2020
// Last Modified: April 10, 2020
// Lab number: 4
// Brief description of the program: This program will consist of 4 inputs and 6 outputs 
// each of the 4 inputs will correspond to a piano note and their corresponding frequencies
// the output will consist of a signal that has been converted from digital to analog
//  
// Hardware connections: 6 resistors, 4 switches, microcontroller, speaker, various jumper cables

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
	Sound_Init(1); // value for systick 
	EnableInterrupts();
	
  while(1){                

	WaitForInterrupt();		// low power mode 
		
  }             
}


