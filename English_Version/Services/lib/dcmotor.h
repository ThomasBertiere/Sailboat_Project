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

//DC motor initialization
void init_DCmotor();

//launch the DC motor
void launch_DCmotor();

//stop the DC motor
void stop_DCmotor();

//modify the impulse duration sent to the DC motor. The duration is in us
void action_DCmotor(float duration_us);

//WARNING : you have to parameterize the neutral value of your remote. It has to be 1.625ms
//return the impulse duration (us) to be sent to the DC motor depending on the received message (impulse duration in ms)
float impulse_duration_DCmotor(float received_duration_ms);