#ifndef SERVO
#define SERVO
#include "servomoteur.h"
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


//retourne l'angle du servo moteur en fonction de l'angle de la voile
int angle_servo(u16 angle_voile){    
	int angle=0;
	if( (angle_voile>=315 && angle_voile<45) ){
		angle=0;
	}
	else if (angle_voile>=45 && angle_voile<181) {
		angle=(int)(((2./3.)*((float)angle_voile))-30.);
	}
	else if(angle_voile>=181 && angle_voile<315){
		angle = (int)(((-2.0)/3.)*((float)angle_voile)+210.);
	}
	return angle;
}


//donne la durée de l'impulsion pour un PWM en fonction de l'angle du servo moteur  
float duree_impulsion_servo(int angle_servo){   
	return ( ((1./90.)*((float)angle_servo) + 1.)*1000.);
}

//mettre le moteur en action grace à un PWM. duree_us doit etre entre 1 et 2 ms 
void init_servo_moteur(){	
	
	Clock_Init_AFIO();
	Clock_Init_GPIO(GPIOA) ; 
	Port_IO_Init_Output(GPIOA,8,1,2) ; 
	Clock_Init() ; 
	Timer_1234_Init_Clock(TIM1) ;
	PWM_Init(TIM1,1,0.,20000.) ; 
	
}

void marche_servo_moteur(){
		Launch_Timer(TIM1);
}

void action_servo_moteur(float duree_us) {
		PWM_Modif_Period(TIM1,1,duree_us,20000.);
		
		
}