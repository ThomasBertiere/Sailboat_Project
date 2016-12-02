#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

//weathercock reset
void weathercock_reset();

//weathercock initialization
void init_weathercock();

//return wind angle 
u16 wind_angle(); 
	