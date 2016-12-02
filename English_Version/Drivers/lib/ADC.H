#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif


/*====ADC=====
*
*=============*/

//enable ADC's clocks
void ADC_Init_Clock(ADC_TypeDef * Adc);
		
//launch ADC acquisition
void ADC_Launch_Acq(ADC_TypeDef * Adc);

//ADC initialization
//		- continuous : 0 or 1 => 0 : single mode 1 : continuous mode
//		- sequence_length : 1 to 16
void ADC_init(ADC_TypeDef * Adc,int continuous, int sequence_length);

//link a channel to a sequence
//		- num_seq : 1 to 16
//		- num_channel : 0 to 17
void ADC_init_sequence_channel(ADC_TypeDef * Adc,int num_seq,int num_channel);

// ACD interrupt (IT) initialization. Priority is the IT priority and fct_IT is the function
// to be launch when the IT is launched
void Adc_init_IT(ADC_TypeDef * Adc,int priority, void (*fct_IT) (void));

//return the ADC value
int Adc_value(ADC_TypeDef * Adc);


/*====WATCHDOG=====
*
*=============*/

//ADC Watchdog initialization  
void Init_ADC_Watchdog(ADC_TypeDef * ADC,int priority, void (* fct_IT)(void));

//Watchdog configuration with a High and Low Threshold 
void ADC_AnalogWatchdogThresholdsConfig ( ADC_TypeDef * ADCx, uint16_t HighThreshold, uint16_t LowThreshold);

//Watchdog configuration on a ADC's channel
void ADC_AnalogWatchdogSingleChannelConfig (ADC_TypeDef * ADCx, int ADC_Channel);

//Watchdog configuration on everry channels of the ADC
void ADC_AnalogWatchdogAllChannelConfig (ADC_TypeDef * ADCx);



