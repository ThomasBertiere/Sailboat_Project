
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
int angle_servo(u16 angle_voile);


//donne la durée de l'impulsion pour un PWM en fonction de l'angle du servo moteur  
float duree_impulsion_servo(int angle_servo);



//mettre le moteur en action grace à un PWM. duree_us doit etre entre 1 et 2 ms 
void init_servo_moteur();

//Lance le servo-moteur
void marche_servo_moteur();

//change la vitesse du servo-moteur
void action_servo_moteur(float duree_us) ;