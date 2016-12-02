#ifndef WEATHERCOCK
#define WEATHERCOCK
#include "weathercock.h"
#endif 

#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef	CLOCK
#define CLOCK
#include "clock.h"
#include "clock_conf.h"
#endif 

#ifndef GPIO
#define GPIO
#include "gpio.h"
#endif

#ifndef TIMER
#define TIMER
#include "timer.h"
#endif 

//weathercock reset
void weathercock_reset() {
	Reset_Valeur_Tim(TIM3);
}

//weathercock initialization
void init_weathercock(){ 	
	Clock_Init();
	Clock_Init_GPIO(GPIOA);
	Port_IO_Init_Input(GPIOA,5,1);
	Port_IO_Init_Input(GPIOA,6,1);
	Port_IO_Init_Input(GPIOA,7,1);
	Timer_1234_Init_Clock(TIM3);
	Init_Tim_Encoder(TIM3,360*4); //la girouette compte jusqu'au quart de degrée
	Init_It_GPIO(GPIOA,5,2,weathercock_reset);

}

//return wind angle 
u16 wind_angle(){ 
	//The timer value is divided by 4 because the weathercock is accurate to 1/4 degree
	return (u16)((float)Valeur_Tim(TIM3))/4.;
}
