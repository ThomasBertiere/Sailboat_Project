#ifndef MOTEURCC
#define MOTEURCC
#include "moteurcc.h"
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


//init le moteurCC
void Init_MotorCC() {
	
	Clock_Init_GPIO(GPIOA) ; 
	Clock_Init();
	
	//init PWM output 
	Clock_Init_AFIO();
	Port_IO_Init_Output(GPIOA,1,1,2) ; 
	Port_IO_Init_Output(GPIOA,2,1,0) ; 
	Timer_1234_Init_Clock(TIM2) ;
	PWM_Init(TIM2,2,0.,20000.) ;
}

//lance le moteurCC
void Marche_MoteurCC(){
	Launch_Timer(TIM2);
}

//stop le moteurCC
void Stop_MoteurCC(){
	PWM_Modif_Period(TIM2,2,0.,20000.);
}

//modifie la valeur de l'impulsion recu par le moteurCC. Prend une duree en us
void Action_MoteurCC(float duree_us) {
	PWM_Modif_Period(TIM2,2,duree_us,20000.);
}

/* ATTENTION, ON REGLE LA TELECOMMANDE TELLE QUE LA VALEUR NEUTRE SOIT DE 1.625ms */
//renvoie la durée d'impulsion en fonction de la durée recu. Prend des ms renvoie des us
float Duree_Impulsion_MoteurCC(float duree_ms_recu) {
	
	float duree_PWM_us=0.;
	if(duree_ms_recu==1.625) {
		duree_PWM_us=0. ; 
	} 
	else if(duree_ms_recu<1.625) { 
		Port_IO_Set(GPIOA,2) ; // SET fait tourner à gauche
		duree_PWM_us=(float)(((-60.24)*duree_ms_recu+107.82)*1000.) ; //passage de ms à us 
		
	}
	else {
		Port_IO_Reset(GPIOA,2) ; //RESET FAIT TOURNER A DROITE
		duree_PWM_us=(float)(((55.86*duree_ms_recu)-80.82)*1000) ; 
	}
	return duree_PWM_us;
}




