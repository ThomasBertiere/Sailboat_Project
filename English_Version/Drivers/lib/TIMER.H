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

//Clock initialization 
void Clock_Init(void)  ; 

//Timer clock initialization
void Timer_1234_Init_Clock(TIM_TypeDef * Timer)  ; 

//Timer configuration. Duration_us is the timer period (us)
void Timer_1234_Init_Duree(TIM_TypeDef * Timer, float Duration_us ) ; 

//PWM initialisation, Duration_PWM_us is the PWM impulse duration (in us), Duration_TIM_us is the Timer period (us)
void PWM_Init(TIM_TypeDef *Timer, char channel, float Duration_PWM_us, float Duration_TIM_us);

//Modification of the PWM impulse duration 
void PWM_Modif_Period(TIM_TypeDef *Timer, char channel, float Duration_PWM_us,float Duration_TIM_us);

//launch timer
void Launch_Timer(TIM_TypeDef *Timer);

//Timer initialization in encoder mode
int Init_Tim_Encoder(TIM_TypeDef *Timer, int reset_value);

//return the timer value
u16 Valeur_Tim(TIM_TypeDef *Timer);

//reset the timer value
void Reset_Valeur_Tim(TIM_TypeDef *Timer);

//timer initialization in input mode 
void init_timer_pwm_input(TIM_TypeDef *Timer, int freq_div);

//return the capture/compare value of the timer for a given channel
u16 CC_Value( TIM_TypeDef *Timer, int channel);


/* ***************
****  IT activation
*/

//overflow IT activation
void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) ) ;

//capture/compare IT activation 
void Timer_Active_IT_CC( TIM_TypeDef *Timer, u8 Priority, int channel, void (*IT_function) (void));