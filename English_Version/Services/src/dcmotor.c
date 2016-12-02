#ifndef DCMOTOR
#define DCMOTOR
#include "dcmotor.h"
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


//DC motor initialization
void init_DCmotor() {
	
	Clock_Init_GPIO(GPIOA) ; 
	Clock_Init();
	
	//init PWM output 
	Clock_Init_AFIO();
	Port_IO_Init_Output(GPIOA,1,1,2) ; 
	Port_IO_Init_Output(GPIOA,2,1,0) ; 
	Timer_1234_Init_Clock(TIM2) ;
	PWM_Init(TIM2,2,0.,20000.) ;
}

//launch the DC motor
void launch_DCmotor(){
	Launch_Timer(TIM2);
}

//stop the DC motor
void stop_DCmotor(){
	PWM_Modif_Period(TIM2,2,0.,20000.);
}

//modify the impulse duration sent to the DC motor. The duration is in us
void action_DCmotor(float duration_us){
	PWM_Modif_Period(TIM2,2,duration_us,20000.);
}

//WARNING : you have to parameterize the neutral value of your remote. It has to be 1.625ms
//return the impulse duration (us) to be sent to the DC motor depending on the received message (impulse duration in ms)
float impulse_duration_DCmotor(float received_duration_ms) {
	
	float PWM_duration_us=0.;
	if(received_duration_ms==1.625) {
		PWM_duration_us=0. ; 
	} 
	else if(received_duration_ms<1.625) { 
		Port_IO_Set(GPIOA,2) ; // SET -> we turn left
		PWM_duration_us=(float)(((-60.24)*received_duration_ms+107.82)*1000.) ; //passage de ms à us 
		
	}
	else {
		Port_IO_Reset(GPIOA,2) ; //RESET -> we turn right
		PWM_duration_us=(float)(((55.86*received_duration_ms)-80.82)*1000) ; 
	}
	return PWM_duration_us;
}




