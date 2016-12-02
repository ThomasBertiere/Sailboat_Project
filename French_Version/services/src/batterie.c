#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif

#ifndef BATTERIE
#define BATTERIE
#include "batterie.h"
#endif 


//fonction à lancer quand la charge est faible
void manque_batterie(){
	stop=1 ; 
};
	
//initialise le controleur de la batterie. Permet de connaitre la charge de la batterie
void init_controleur_batterie(){
	ADC_Init_Clock(ADC2);
	ADC_init(ADC2,1,1);
	ADC_init_sequence_channel(ADC2,1,12);
	ADC_Launch_Acq(ADC2);
}

//renvoie la charge de la batterie
int charge_batterie(){
	return (int)((((float)Adc_recup_valeur(ADC2))*6.0)/528.0);
}

//fonction permettant d'associer une charge limite à la batterie. Val_limite est en V.
void init_charge_limite(int val_limite){

	int val_lim_hexa=(int)((((float)val_limite)*528.0)/6.0);
	Init_ADC_Watchdog(ADC2,4,manque_batterie);
	ADC_AnalogWatchdogThresholdsConfig(ADC2,10000,val_lim_hexa);//10000 est la valeur limite haute. On ne la considère pas ici. On met donc une grosse valeur
	ADC_AnalogWatchdogSingleChannelConfig(ADC2,12);
}
	
	
