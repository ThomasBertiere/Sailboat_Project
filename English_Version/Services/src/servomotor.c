#ifndef SERVO
#define SERVO
#include "servomotor.h"
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


//return servomotor angle considering wind angle
int servomotor_angle(u16 wind_angle){
	
	int angle=0;
	if( (wind_angle>=315 && wind_angle<45) ){
		angle=0;
	}
	else if (wind_angle>=45 && wind_angle<181) {
		angle=(int)(((2./3.)*((float)wind_angle))-30.);
	}
	else if(wind_angle>=181 && wind_angle<315){
		angle = (int)(((-2.0)/3.)*((float)wind_angle)+210.);
	}
	return angle;
}


//give the impulse duration to the PWM Timer considering the servomotor angle  
float servomotor_impluse_duration(int servo_angle){ 
	return ( ((1./90.)*((float)servo_angle) + 1.)*1000.);
}


//servomotor initialization
void init_servomotor(){	
	
	Clock_Init_AFIO();
	Clock_Init_GPIO(GPIOA) ; 
	Port_IO_Init_Output(GPIOA,8,1,2) ; 
	Clock_Init() ; 
	Timer_1234_Init_Clock(TIM1) ;
	PWM_Init(TIM1,1,0.,20000.) ; 
	
}

//Launch the servomotor
void launch_servomotor(){
	Launch_Timer(TIM1);
}

//change servomotor position by giving a duration in us. This duration will be transfer to a PWM timer.
//duration_us should be between 1 and 2 ms 
void action_servomotor(float duration_us){
		PWM_Modif_Period(TIM1,1,duration_us,20000.);
}