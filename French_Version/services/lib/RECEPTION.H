#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef TIM
#define TIM
#include "timer.h"
#endif

#ifndef GPIO
#define GPIO
#include "gpio.h"
#endif

#ifndef	CLOCK
#define CLOCK
#include "clock.h"
#include "clock_conf.h"
#endif 

//initialise la reception
void init_reception();

//lance la r�ception
void launch_reception();

//lorsque cette fonction est appell�e elle r�cup�re la dur�e de l'impulsion recu en ms
float duree_impulsion_recu();
    
