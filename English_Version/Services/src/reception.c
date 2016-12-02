#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef	CLOCK
#define CLOCK
#include "clock.h"
#include "clock_conf.h"
#endif 

#ifndef TIM
#define TIM
#include "timer.h"
#endif

#ifndef GPIO
#define GPIO
#include "gpio.h"
#endif

#ifndef RECEP
#define RECEP
#include "reception.h"
#endif 

//local variable  
u16 impluse_duration;

//in background, every impluse reception, the system save this value in the variable impluse_duration
void fct_IT(){
	impluse_duration=CC_Value(TIM4,2);
}

//reception initialization
void init_reception(){
	
	Clock_Init();
	Clock_Init_GPIO(GPIOB);
	Port_IO_Init_Input(GPIOB,6,1);
	impluse_duration=0 ; 
	Timer_1234_Init_Clock(TIM4);
	init_timer_pwm_input(TIM4,1000);
	Timer_Active_IT_CC(TIM4,3,2,fct_IT);
}

//launch reception
void launch_reception(){
	Launch_Timer(TIM4);		
}

//when this function is called it returns the impulse duration of the received signal in ms
float received_impulse_duration(){
	return (((float)impluse_duration)*(1000000./72000000.0));
}

