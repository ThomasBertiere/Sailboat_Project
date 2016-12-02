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

#ifndef WEATHERCOCK
#define WEATHERCOCK
#include "weathercock.h"
#endif 

#ifndef SERVO
#define SERVO
#include "servomotor.h"
#endif 

#ifndef BATTERY
#define BATTERY
#include "battery.h"
#endif 

#ifndef RECEP
#define RECEP
#include "reception.h"
#endif 

#ifndef DCMOTOR
#define DCMOTOR
#include "dcmotor.h"
#endif

#ifndef ROULLING
#define ROULLING
#include "rolling.h"
#endif 

#ifndef USART
#define USART
#include "usart.h"
#endif

#ifndef TIMER_SYSTICK
#define TIMER_SYSTICK
#include "Timer_Systick.h"
#endif

int cpt ; 
int mode; 





void scheduler_systick() {
	/*
	-- SCHEDULING 
	-- TICK EVERY 167ms
	-- ONE TICK OVER THREE : 
	--   * Weathercock + PWM servomotor      -> 1/501ms  => too long
	--   * Boat rolling monitoring 					 -> 1/501ms	 
	--	 * Remote's signal reception + PWM DC motor	 -> 1/501ms  => too long
	*/
	
	//If no more battery, we stop DC motor and we block the system  
	if(stop==0) {
		if(cpt==0) {
			//If boat rolling is too high, we do not move servomotor
			if(mode==0) {
				//Weathercock + PWM servomotor  
				action_servomotor(servomotor_impluse_duration(servomotor_angle(wind_angle()))) ;
			}
			cpt++ ; 
		} 
		else if(cpt==1){	
			//Boat rolling monitoring
			rolling_angle_checking();	
			cpt++ ; 
		}
		else {
			//Remote'signal reception + PWM DC motor	
			//WARNING : you have to parameterize the neutral value of your remote. It has to be 1.625ms
			action_DCmotor(impulse_duration_DCmotor(received_impulse_duration()));
			cpt=0 ; 
		}
	}
	else {
		stop_DCmotor();
	}
	
}

 
int main (void){
	
	//=============Systick Initialization==========================================
	//=============SysTick
	//167ms car 501ms/3 
	CLOCK_Configure() ; 
	Systick_Period(167000) ;
	Systick_Prio_IT(1,scheduler_systick);
	SysTick_On ; //lance le systick 
	SysTick_Enable_IT ; //enable l'IT 
	
	//=============Weathercock Initialization======================================
	//=============GPIOA.5,6,7 TIM3-CH2
	init_weathercock();  
	
	//============Servomotor Initialization========================================
	//============GPIOA.8 TIM1-CH1
	init_servomotor() ; 
	launch_servomotor() ;
		
	//============Reception Initialization=========================================
	//============GPIOB.6 TIM4-CH2
	init_reception();
	launch_reception();
	
	//============DC Motor Initialization==========================================
	//============GPIOA.1,2 TIM2-CH2
	init_DCmotor();
	launch_DCmotor();
	
	//============Boat rolling monitoring Initialization ==========================
	//============ADC-CH10
	init_rolling_monitoring() ;
	launch_rolling_monitoring() ;
  
	//============Battery monitoring Initialization ===============================
	//============ADC-CH12
	init_battery_monitoring() ; 
	init_limit_value_battery(10) ;
	
	//=============Global variables Initialization ================================
	//=============cpt, mode, stop
	mode=0 ; 
	cpt=0 ;
	stop=0 ; 
	
	
	
	//=============USART TEST================================	
	//Init_Usart_Emission(USART1) ;
	//Send_Transmission(USART1,'c') ;
	//========================================================
	
	while(1){};
		
	return 0;

}