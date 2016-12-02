
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
int servomotor_angle(u16 wind_angle);

//give the impulse duration to the PWM Timer considering the servomotor angle  
float servomotor_impluse_duration(int servo_angle);

//servomotor initialization
void init_servomotor();

//Launch the servomotor
void launch_servomotor();

//change servomotor position by giving a duration in us. This duration will be transfer to a PWM timer.
//duration_us should be between 1 and 2 ms 
void action_servomotor(float duration_us) ;