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
#include "Sound.h"
#include "Piano.h" 

// put code definitions for the software (actual C code)
// this file explains how the module works

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	//what port for DAC Init 
	// for example we can use PORTE
	//on portE pins 0-5 will be used for output
	int x = 0;
	SYSCTL_RCGC2_R |= 0x10;
	x++;
	GPIO_PORTE_DEN_R |=0x3F;
	GPIO_PORTE_DIR_R |=0x3F; //
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
