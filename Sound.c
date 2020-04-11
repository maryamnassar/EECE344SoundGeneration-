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
#include "dac.h"
#include "piano.h" 
// put code definitions for the software (actual C code)
// this file explains how the module works
int SinWaveSound[64] = {32,35,38,41,44,46,49,51,
												54,56,58,59,61,62,62,63,
												63,63,62,62,61,59,58,56,
												54,51,49,46,44,41,38,35,
												32,28,25,22,19,17,14,12,
												9,7,5,4,2,1,1,0,
												0,0,1,1,2,4,5,7,
												9,12,14,17,19,22,25,28};
volatile unsigned long frequency; 
unsigned long Index = 0; 
// Sin wave table for digital sound synthesis 
// RELOAD VAL = [((Fbus in MHz)/((Fnote in Hz)(INDEX VAL))]-1 					
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Input: Initial interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(unsigned long period){
		//steps below outline the method to initialize systick 
		DAC_Init (); //Initialize DAC (digital to analog converter)
		NVIC_ST_CTRL_R = 0; //Disable systick
		NVIC_ST_RELOAD_R = period-1; //the reload value will be the period - 1 (subtract 1 bc we start count from 0) 
		NVIC_ST_CURRENT_R = 0; //clear current register, this is the true reflection of the counter 
		NVIC_ST_CTRL_R = 0x7; // enable again 
		NVIC_EN0_R = 0x40000000; 
		Index = 0;// refernce PG 215, init Index to 0 
		frequency = 0; 
}

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//           input of zero disables sound output
// Output: none
void Sound_Play(unsigned long frequency){
	// using portE for DAC 
		// directions are update the reload register with
		// the recquired delay value for the note specified 
		// clear the current register everytime we update the ReloadR

	if (frequency == 0) {
	NVIC_ST_CTRL_R = 0; 
	} else {
		NVIC_ST_RELOAD_R = frequency; 
		NVIC_ST_CURRENT_R = 0;
		NVIC_ST_CTRL_R = 0x07;
			}
	}
  
// Interrupt service routine
// Executed periodically, the actual period
// determined by the current Reload.
void SysTick_Handler(void){
	//for sound output using periodic interrupts
	// input if from DAC portE 
				Index = (Index + 1)&0x3F; // cycle through values 
				DAC_Out(SinWaveSound[Index]); //output 1 for each interrupt request
		
	}
// Piano Keys Interrupt service routine
// executed on both edges of switch input. 
// add the edge triggered interrupt handler here.
 

			
