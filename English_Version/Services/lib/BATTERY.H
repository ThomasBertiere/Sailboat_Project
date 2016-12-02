#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif


//initialization of the battery monitoring system
void init_battery_monitoring();

//return the battery lever
int battery_level();

//function to give the battery a limit value. This limit value is in Volt
void init_limit_value_battery(int limit_val);
	
//variable globale mise à 1 quand la batterie passe sous un certain seuil 
int stop ; 
