#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif

#ifndef ROLLING
#define ROLLING
#include "rolling.h"
#endif 



//function to be call when the boat rolling angle is greater than 45°
void angle_exceeded()  {
	/* ----------TO BE DONE------------
	-- USART MESSAGES SENDING */
	//Thanks to this global variable we stop the sail sheeting 
	mode=1 ; 
}


//check the boat rolling angle
void rolling_angle_checking() {
	int val = Adc_value(ADC1); 
	
	//low and high threshold have to be modify depending on th model sailboat 
	int low_threshold = 1400 ; 
	int high_threshold = 2060 ; 
	
	if((val<low_threshold)||(val>high_threshold)) {
		if(!mode) 
		{	angle_exceeded() ; }
	} else if(mode) { 
			mode=0  ;
	}
}


//initialization of the boat rolling monitoring 
void init_rolling_monitoring() {
	ADC_Init_Clock(ADC1);
	ADC_init(ADC1,1,1);
	ADC_init_sequence_channel(ADC1,1,10);
}	

//launch the boat rolling monitoring 
void launch_rolling_monitoring() {
	ADC_Launch_Acq(ADC1);
}



