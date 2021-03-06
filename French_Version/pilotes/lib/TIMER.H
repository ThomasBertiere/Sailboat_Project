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

#ifndef ADC
#define ADC
#include "adc.h"
#endif

/**
* Configure la clock 
**/
void Clock_Init(void)  ; 

/**
* Active la clock pour le timer pass� en param�tre 
* @param Timer pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer consid�r�
**/
void Timer_1234_Init_Clock(TIM_TypeDef * Timer) ; 


/** 
* Configure les Timers 1, 2, 3 et 4
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer consid�r�
* @param Duree_us Intervalle de temps exprim� en �s entre
* deux d�bordements successifs
* @return Le dur�e v�ritable qui a �t� configur�e
**/
void Timer_1234_Init_Duree(TIM_TypeDef * Timer, float Duree_us ) ; 

/**
* Configure la routine d'interruption d'un Timer
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef ) du
* timer consid�r�
* @param Priority Niveau de priorit� de l'interruption
* @param IT_function Pointeur sur la fonction qui sera ex�cut�e dans le routine
d'interruption
**/
void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) );

/**
* Cette fonction initialise la voie sp�cifi�e du timer voulu en PWM.
* La fr�quence souhait�e est pass�e en param�tre.
* La fonction renvoie un entier qui correspond � la r�solution de la PWM pour
* pouvoir ensuite r�gler les rapports cycliques.
*
* 3 Timer "general Purpose", TIM2, TIM3 et TIM4 + TIM1
* Chacun d'entre eux dispose de 4 voies de sorties num�rot�es de 1 � 4
* Mapping des IO:
* TIM1_CH1 - PA08 TM2_CH1_ETR - PA0 TM3_CH1 - PA6 TIM4_CH1 - PB6
* TIM1_CH1 - PA09 TM2_CH2 - PA1 TM3_CH2 - PA7 TIM4_CH2 - PB7
* TIM1_CH1 - PA10 TM2_CH3 - PA2 TM3_CH3 - PB0 TIM4_CH3 - PB8
* TIM1_CH4 � PA11 TM2_CH4 - PA3 TM3_CH4 - PB1 TIM4_CH4 - PB9
**/
void PWM_Init(TIM_TypeDef *Timer, char Voie, float Dureee_PWM_us, float Duree_TIM_us);
/*
* Permet de modifier la p�riode du PWM 
* @param Timer Pointeur vers le timer associ�
* @param Voie channel du timer concern�
* @Duree_PWM_us P�riode la PWM en us 
* @Duree_TIM_us P�riode du timer en us 
*/
void PWM_Modif_Period(TIM_TypeDef *Timer, char Voie, float Duree_PWM_us,float Duree_TIM_us);
/**
* Launch counter du Timer pass� en param
**/
void Launch_Timer(TIM_TypeDef *Timer) ; 

//initialise un timer en mode encodeur sur deux voies 
int Init_Tim_Encoder(TIM_TypeDef *Timer, int valeur_remise_a_zero);

//r�cup�re la valeur du timer
u16 Valeur_Tim(TIM_TypeDef *Timer);

//reset la valeur du timer 
void Reset_Valeur_Tim(TIM_TypeDef *Timer);

//initialise un tiler en mode PWM input ; freq_div est la valeur par laquelle la fr�quence du syst�me est divis� 
void init_timer_pwm_input(TIM_TypeDef *Timer, int freq_div);

//renvoie la valeur du registre CCx o� x=channel
u16 Valeur_CC( TIM_TypeDef *Timer, int channel);

//active l'IT associ� au capture compare asssoci� au channel 
void Timer_Active_IT_CC( TIM_TypeDef *Timer, u8 Priority, int channel, void (*IT_function) (void));