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

//reception initialization
void init_reception();

//launch reception
void launch_reception();

//when this function is called it returns the impulse duration of the received signal in ms
float received_impulse_duration();
    
