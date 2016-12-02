//__________________________________________________________
// TRINOME : BERTIERE Thomas , DE BRITO Guillaume, DESPLATS Rama
// ETAT : Toujours en vie 
// GROUPE : 4I-B2
//__________________________________________________________

//____ registres de périphériques du stm_32

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

#ifndef GIROUETTE
#define GIROUETTE
#include "girouette.h"
#endif 

#ifndef SERVO
#define SERVO
#include "servomoteur.h"
#endif 

#ifndef BATTERIE
#define BATTERIE
#include "batterie.h"
#endif 

#ifndef RECEP
#define RECEP
#include "reception.h"
#endif 

#ifndef MOTEURCC
#define MOTEURCC
#include "moteurcc.h"
#endif

#ifndef ROULIS
#define ROULIS
#include "roulis.h"
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





void notre_boucle_systick() {
	/*
	-- ORDONANCEMENT 
	-- TICK TOUTES LES 167ms
	-- 1 TICK SUR TROIS : 
	--   * CALCUL GIROUETTE + PWM SERVO-MOTEUR -> 1/501ms  => TROP LONG 
	--   * CONTROLE ROULIS										 -> 1/501ms	 
	--	 * INFOS MANETTE + PWM MOTEUR CC 			 -> 1/501ms  => TROP LONG
	*/
	
	//Si plus de batterie, on ne fait plus rien et on stoppe le moteur  
	if(stop==0) {
		if(cpt==0) {
			//Si le bâteau est trop penché, on ne récupère plus la valeur de la girouette et on ne fait plus bouger le servo-moteur
			if(mode==0) {
				//Calcul girouette + servo
				action_servo_moteur(duree_impulsion_servo(angle_servo(angle_vent()))) ;
			}
			cpt++ ; 
		} 
		else if(cpt==1){	
			//CONTROLE ROULIS
			Recup_Angle();	
			cpt++ ; 
		}
		else {
			//LIRE INFOS MANETTE + ACTION MOTEUR CC 
			//ATTENTION REGLER LA MANETTE SUR UNE VALEUR NEUTRE DE 1.625ms !!!
			Action_MoteurCC(Duree_Impulsion_MoteurCC(duree_impulsion_recu()));
			cpt=0 ; 
		}
	}
	else {
		Stop_MoteurCC();
	}
	
}

 
int main (void){
	
	//=============Initialisation Systick=================
	//=============SysTick
	//167ms car 501ms/3 
	CLOCK_Configure() ; 
	Systick_Period(167000) ;
	Systick_Prio_IT(1,notre_boucle_systick);
	SysTick_On ; //lance le systick 
	SysTick_Enable_IT ; //enable l'IT 
	
	//=============Init Girouette============================
	//=============GPIOA.5,6,7 TIM3-CH2
	init_girouette() ;  
	
	//============Init Servo-moteur==========================
	//============GPIOA.8 TIM1-CH1
	init_servo_moteur() ; 
	marche_servo_moteur() ;
		
	//============Init Reception=============================
	//============GPIOB.6 TIM4-CH2
	init_reception();
	launch_reception();
	
	//============Init MoteurCC==============================
	//============GPIOA.1,2 TIM2-CH2
	Init_MotorCC();
	Marche_MoteurCC();
	
	//============Init Roulis================================
	//============ADC-CH10
	Init_Controle_Roulis() ;
	Controle_Roulis() ;
  
	//ATTENTION NE PAS LAISSER EN SIMU CAR AUCUNE TENSION EN ENTREE
	//============Init batterie==============================
	//============ADC-CH12
	init_controleur_batterie() ; 
	init_charge_limite(6) ; //limite 6V    //ATTENTION PROBLEME DE CHUTE DE TENSION LORS DE L'ACTION DU MOTEUR CC 										

	//=============Initialisation variables globales
	//=============cpt, mode, stop
	mode=0 ; 
	cpt=0 ;
	stop=0 ; 
	
	
	
	
	//=============PARTIE TEST USART================================
	//Init du USART et ex de transmission	
	//Init_Usart_Emission(USART1) ;
	//Send_Transmission(USART1,'c') ;
	//========================================================
	
	while(1){
		/* --- A FAIRE ----
		-- TRAITEMENTS USART 
		
		//Send_Transmission(USART1,'c') ;
		*/
		

	};
		
	return 0;

}