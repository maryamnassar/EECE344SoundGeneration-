// dac.c
// This software configures DAC output
// Runs on TM4C123
// Program written by: put your names here
// Date Created: 
// Last Modified: 
// Lab number: 4
// Hardware connections

#include "tm4c123gh6pm.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	//what port for DAC Init 
	// for example we can use PORTE
	//on portE pins 0-3 will be used for input
	int x = 0;
	SYSCTL_RCGC2_R |= 0x10;
	x++;
	GPIO_PORTE_DEN_R |=0x3F;
	GPIO_PORTE_DIR_R |=0x3F;
	GPIO_PORTE_AFSEL_R &=~0x3F;
	GPIO_PORTE_AMSEL_R &=~0x3F;
	
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Output: none
void DAC_Out(unsigned long data){

	GPIO_PORTE_DATA_R = data; 
	
}
