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

//variable des réceptions
u16 duree_imp;

//en arrière plan, toute les impulsion recu, le système enregistre sa durée dans duree_imp
void fct_IT(){
	duree_imp=Valeur_CC(TIM4,2);
}

//initialise la reception
void init_reception(){
	
	Clock_Init();
	Clock_Init_GPIO(GPIOB);
	Port_IO_Init_Input(GPIOB,6,1);
	duree_imp=0 ; 
	Timer_1234_Init_Clock(TIM4);
	init_timer_pwm_input(TIM4,1000);
	Timer_Active_IT_CC(TIM4,3,2,fct_IT);
}

//lance la reception
void launch_reception(){
	Launch_Timer(TIM4);		
}

//lorsque cette fonction est appellée elle récupère la durée de l'impulsion recu en ms
float duree_impulsion_recu(){
	return (((float)duree_imp)*(1000000./72000000.0));
}

