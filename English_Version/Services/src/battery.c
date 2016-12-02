#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif

#ifndef BATTERY
#define BATTERY
#include "battery.h"
#endif 


//function to be launch when battery level is low
void no_battery(){
	stop=1 ; 
};
	
//initialization of the battery monitoring system
void init_battery_monitoring(){
	ADC_Init_Clock(ADC2);
	ADC_init(ADC2,1,1);
	ADC_init_sequence_channel(ADC2,1,12);
	ADC_Launch_Acq(ADC2);
}

//return the battery lever
int battery_level(){
	return (int)((((float)Adc_value(ADC2))*6.0)/528.0);
}

//function to give the battery a limit value. This limit value is in Volt
void init_limit_value_battery(int limit_val){

	int limit_val_hexa=(int)((((float)limit_val)*528.0)/6.0);
	Init_ADC_Watchdog(ADC2,4,no_battery);
	ADC_AnalogWatchdogThresholdsConfig(ADC2,10000,limit_val_hexa);//As 10 000 is the high value, we do not consider it here.
	ADC_AnalogWatchdogSingleChannelConfig(ADC2,12);
	
}
	
	
