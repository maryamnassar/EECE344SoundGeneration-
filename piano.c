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
// put code definitions for the software (actual C code)
// this file explains how the module works
#define A = 2272; //440Hz for reload value 
#define B = 2023;	//494Hz for reload value 
#define C = 3816;	//262Hz for reload value 
#define D = 3400;	//294Hz for reload value 
unsigned long input; 
unsigned long key; 

// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void Piano_Init(void){ 
	//using PD 0-3 for inputs 
	// using bits 0000 1111 for inputs 
	int x = 0;
	SYSCTL_RCGC2_R |=0x08; 
	x++;
	GPIO_PORTD_DIR_R &=~0x0F; //bits 0-3 are for inputs -- 0 written to them as inputs 
	GPIO_PORTD_DEN_R |=0x0F;
	GPIO_PORTD_AFSEL_R &=~0x0F;
	GPIO_PORTD_AMSEL_R &=~0x0F; 
	//for enabling interrupts
	//for portD
	//Enable interrupts on all switches on both edges
	GPIO_PORTD_IS_R &= ~0x0F; //PD 0-3 IS EDGE SENSITIVE
	GPIO_PORTD_IBE_R |= 0x0F; //PC4 IS BOTH EDGE
	GPIO_PORTD_IEV_R = 0x00; //ACCORDING TO PAGE 331 WE WRITE NOTHING TO THIS?
	GPIO_PORTD_ICR_R = 0x0F; // CLEAR FLAG....IS IT FLAG 4? IF SO CLEAR 0x10
	GPIO_PORTD_IM_R |= 0x0F; //ARM BIT IS SET FOR PD 0-3
	NVIC_PRI0_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000;
	NVIC_EN0_R = 0x08;
	input = 0; 
	key = 0; 
	
	// ** note we use PRI0 as specified in table 12.2
}
// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2 and 0x08 is just key3

// 0x01 = Key0 = A = 440
// 0x02 = Key1 = B = 494
// 0x04 = Key2 = C = 262
// 0x08 = Key3 = D = 294 


unsigned long Piano_In(void){ 
		key = GPIO_PORTD_DATA_R; 
		return key; 
	// we can use if else statemetns for each key in put 
	// each key input is assigned a freq value to output
	// our INPUT comes from portD... our piano keys
	// our OUTPUT comes from portE... our DAC 
}


// Insert the Handler for key input according to your output choice
// refer to start.s for ISR names
void GPIOPortD_Handler(void) {
		//acknowledge the interrups 
		input = Piano_In(); 
		GPIO_PORTD_ICR_R = 0x0F; //clear flag that was triggered for the interrupt Reg PG 325 in Book 

			if (input == 0x01) { //note A
				Sound_Play(2840); // call sound play function 2840
			} else if (input == 0x02) { //note B 
				Sound_Play(2529); //2529
			} else if (input == 0x04) {  //note C
				Sound_Play(4770);//4770
			} else if (input == 0x08){ //note D
				Sound_Play(4250);//4250
				} else {
				Sound_Play(0);
						}
		// all 4 keys interrupt at both edges -- PD is inputs
		// insdie the handler we define what actions take
		// place if any of the keys are altered 
			}

