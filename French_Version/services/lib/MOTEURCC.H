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

//renvoie la durée d'impulsion en fonction de la durée recu. Prend des ms renvoie des us
float Duree_Impulsion_MoteurCC(float duree_ms_recu);

//initialise le moteurCC
void Init_MotorCC();

//lance le moteurCC
void Marche_MoteurCC();

//stop le moteurCC
void Stop_MoteurCC();

//modifie la valeur de l'impulsion recu par le moteurCC. Prend une duree en us
void Action_MoteurCC(float duree_us);