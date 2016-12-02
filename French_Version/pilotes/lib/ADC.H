#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif


/*====ADC=====
*
*=============*/
//enable la clock des ADC
void ADC_Init_Clock(ADC_TypeDef * Adc);
	
//lance l'acquisition
void ADC_Launch_Acq(ADC_TypeDef * Adc);

//initialise l'ADC
//		- continuous : 0 ou 1 => 0 : single mode 1 : continuous mode
//		- sequence_length : 1 à 16
void ADC_init(ADC_TypeDef * Adc,int continuous, int sequence_length);

//associe un channel à une sequence
//		- num_seq : entre 1 et 16
//		- num_channel : entre 0 et 17
void ADC_init_sequence_channel(ADC_TypeDef * Adc,int num_seq,int num_channel);

//associe une fonction à lancer à la fin d'une conversion (par IT), à un ADC avec une priorité
void Adc_init_IT(ADC_TypeDef * Adc,int priorite, void (*fct_IT) (void));

//récupère la valeur de sortie de l'ADC 
int Adc_recup_valeur(ADC_TypeDef * Adc);


/*====WATCHDOG=====
*
*=============*/

//initialise le Watchdog sur l'ADC  
void Init_ADC_Watchdog(ADC_TypeDef * ADC,int priorite, void (* ptrFonction)(void));

//configure le watchog avec une valeur haute et une valeur basse
void ADC_AnalogWatchdogThresholdsConfig ( ADC_TypeDef * ADCx, uint16_t HighThreshold, uint16_t LowThreshold);

//configure le watchdog d'un ADC sur un channel
void ADC_AnalogWatchdogSingleChannelConfig (ADC_TypeDef * ADCx, int ADC_Channel);

//configure le watchdog d'un ADC sur tous les channels 
void ADC_AnalogWatchdogAllChannelConfig (ADC_TypeDef * ADCx);



