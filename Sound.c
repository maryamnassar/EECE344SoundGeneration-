// Sound.c, 
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 
// Last Modified:  
// Lab number: 5
// Hardware connections
#include "tm4c123gh6pm.h"
#include "dac.h"
#include "piano.h" 

// put code definitions for the software (actual C code)
// this file explains how the module works
int SinWaveSound[22] = {0x20,0x28,0x31,0x37,0x3c,0x3f,0x3f,0x3c,
												0x37,0x31,0x28,0x20,0x17,0xe,0x8,0x3,
												0x0,0x0,0x3,0x8,0xe,0x17};
int Frequency[4] = {8263, 7360, 13878, 12368};
volatile unsigned long WaveFrequency; 
volatile unsigned long frequency; 
								
// Sin wave table for digital sound synthesis 
//selected value of 80 points with a max amplitude of 63
// the max value of 63 is based on the 6 bit binary weighted dac output limit we were given in the lab manual 
// Add the sine wave data structure here

volatile unsigned long Index; 
// RELOAD VAL = [((Fbus in MHz)/((Fnote in Hz)(INDEX VAL))]-1 
								
								
// from lab manual we know that Fwave = Fnote*80
// we use 80 because it is the size of our table

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
		NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; //set priotity
		NVIC_ST_CTRL_R = 0x07; // enable again 
		Index = 0;// refernce PG 215, init Index to 0 
		frequency = 0; 
		WaveFrequency = 0; 
}

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disables sound output
// Output: none
void Sound_Play(unsigned long frequency){
	// using portE for DAC 
		// directions are update the reload register with
		// the recquired delay value for the note specified 
		// clear the current register everytime we update the ReloadR
		frequency = GPIO_PORTD_DATA_R; 
		NVIC_ST_RELOAD_R = frequency; 
		//NVIC_ST_CURRENT_R = (frequency - 1) & 0x00FFFFFF; 
		NVIC_ST_CURRENT_R = 0X00; 
	}
  
// Interrupt service routine
// Executed periodically, the actual period
// determined by the current Reload.
void SysTick_Handler(void){
	//for sound output using periodic interrupts
	// input if from DAC portE 
	GPIO_PORTE_DATA_R ^= 0x0F; // toggle bits 0 - 3 
				DAC_Out(SinWaveSound[Index]); //output 1 for each interrupt request
				Index = (Index + 1);
		if (Index > 21) {
				Index = 0; 
		}
}
// Piano Keys Interrupt service routine
// executed on both edges of switch input. 
// add the edge triggered interrupt handler here.
// 

			
