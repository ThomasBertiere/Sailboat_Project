#ifndef GIROUETTE
#define GIROUETTE
#include "girouette.h"
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

//reset la girouette
void reset_girouette() {
	Reset_Valeur_Tim(TIM3);
}

//initialise la girouette
void init_girouette(){ 	
	Clock_Init();
	Clock_Init_GPIO(GPIOA);
	Port_IO_Init_Input(GPIOA,5,1);
	Port_IO_Init_Input(GPIOA,6,1);
	Port_IO_Init_Input(GPIOA,7,1);
	Timer_1234_Init_Clock(TIM3);
	Init_Tim_Encoder(TIM3,360*4); //la girouette compte jusqu'au quart de degrée
	Init_It_GPIO(GPIOA,5,2,reset_girouette);

}

//retourne l'angle du vent 
u16 angle_vent(){ 
	//la valeur du timer est divisée par 4 car le codeur incrémental est précis au quart de degrès
	return (u16)((float)Valeur_Tim(TIM3))/4.;
}
