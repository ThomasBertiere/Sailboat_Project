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



//global function pointer for handlers
void (*ptr_fct_timer) (void) ; 

/* *************
***HANDLERS
*/
void TIM2_IRQHandler(void) {
	(*ptr_fct_timer)()  ;  
	//Overflow IT desactivation
	TIM2->SR&=~(TIM_SR_UIF) ; 
	//capture/compare IT desactivation 
	TIM2->SR&=~(TIM_SR_CC1IF|TIM_SR_CC2IF|TIM_SR_CC3IF|TIM_SR_CC4IF) ; 
}

void TIM3_IRQHandler(void) {
	(*ptr_fct_timer)()  ;
	//Overflow IT desactivation
	TIM3->SR&=~(TIM_SR_UIF) ; 
	//capture/compare IT desactivation 
	TIM3->SR&=~(TIM_SR_CC1IF|TIM_SR_CC2IF|TIM_SR_CC3IF|TIM_SR_CC4IF) ; 
}

void TIM4_IRQHandler(void) {
	(*ptr_fct_timer)()  ;
	//Overflow IT desactivation
	TIM4->SR&=~(TIM_SR_UIF) ; 	
	//capture/compare IT desactivation 
	TIM4->SR&=~(TIM_SR_CC1IF|TIM_SR_CC2IF|TIM_SR_CC3IF|TIM_SR_CC4IF) ; 
}




















//Clock initialization 
void Clock_Init(void) {
	CLOCK_Configure() ; 
}

//Timer clock initialization
void Timer_1234_Init_Clock(TIM_TypeDef * Timer) {
	if(Timer==TIM1) RCC->APB2ENR|=RCC_APB2ENR_TIM1EN ; 
	else if(Timer==TIM2) RCC->APB1ENR|=RCC_APB1ENR_TIM2EN ; 
	else if(Timer==TIM3) RCC->APB1ENR|=RCC_APB1ENR_TIM3EN ;  
	else if(Timer==TIM4) RCC->APB1ENR|=RCC_APB1ENR_TIM4EN ;  
}

 
//Timer configuration. Duration_us is the timer period
void Timer_1234_Init_Duree(TIM_TypeDef * Timer, float Duration_us ) { 
	
	//Downcounting
	Timer->CR1|=TIM_CR1_DIR ; 
	
	/*
	PSC and ARR :
	*/
	float freq = ((float)(CLOCK_GetTIMCLK (Timer)))/(1./(Duration_us/1000000.));
	float psc = (freq/65536.) ;
	//rounded up
	if(((int)psc/psc)!=1) psc=((int)psc)+1 ;  
	Timer->PSC=(u16)(psc-1) ; 
	float arr = freq / psc ; 
	//rounded up
	if(((int)arr/arr)!=1) arr=((int)arr)+1 ;
	Timer->ARR=(u16)(arr-1) ; 

}

//PWM initialisation, Duration_PWM_us is the PWM impulse duration (in us), Duration_TIM_us is the Timer period (us)
void PWM_Init(TIM_TypeDef *Timer, char channel, float Duration_PWM_us, float Duration_TIM_us) {

	Timer->CR1|=TIM_CR1_DIR ; 
	
	float Freq_TIM = (1000000./Duration_TIM_us) ; 
	float Freq_PWM = (1000000./Duration_PWM_us) ; 
	
	
	/*
	PSC and ARR
	*/
	float freq = ((float)(CLOCK_GetTIMCLK (Timer)))/Freq_TIM;
	float psc = (freq/65536.) ;
	//rounded up
	if(((int)psc/psc)!=1) psc=((int)psc)+1 ;  
	Timer->PSC=(u16)(psc-1) ; 
	float arr = freq / psc ; 
	//rounded up
	if(((int)arr/arr)!=1) arr=((int)arr)+1 ;
	Timer->ARR=(u16)(arr-1) ; 
	
	
	/**
	* CONFIG PWM 
	*/
	float ccr = ((1.)-(Freq_TIM/Freq_PWM))*arr ;
	if(channel==1) {
		//output channel 1 activation 
		Timer->CCER|=TIM_CCER_CC1E ; 
		//output activation
		Timer->CCMR1&=~(TIM_CCMR1_CC1S) ; 
		//mode 2 
		Timer->CCMR1|=TIM_CCMR1_OC1M ; 
		//compare value
		Timer->CCR1&=0 ; 
		Timer->CCR1|=(u16)ccr ; 
	}
	else if (channel==2) {
		//output channel 1 activation 
		Timer->CCER|=TIM_CCER_CC2E ; 
		//output activation
		Timer->CCMR1&=~(TIM_CCMR1_CC2S) ; 
		//mode 2 
		Timer->CCMR1|=TIM_CCMR1_OC2M ; 
		//compare value
		Timer->CCR2&=0 ; 
		Timer->CCR2|=(u16)ccr ; 
	}
	else if (channel==3) {
		//output channel 1 activation 
		Timer->CCER|=TIM_CCER_CC3E ; 
		//output activation
		Timer->CCMR2&=~(TIM_CCMR2_CC3S) ; 
		//mode 2 
		Timer->CCMR2|=TIM_CCMR2_OC3M ; 
		//compare value
		Timer->CCR3&=0 ; 
		Timer->CCR3|=(u16)ccr ; 
	}
	else if (channel==4) {
		//output channel 1 activation 
		Timer->CCER|=TIM_CCER_CC4E ; 
		//output activation
		Timer->CCMR2&=~(TIM_CCMR2_CC4S) ; 
		//mode 2 
		Timer->CCMR2|=TIM_CCMR2_OC4M ; 
		//compare value
		Timer->CCR4&=0 ; 
		Timer->CCR4|=(u16)ccr ; 
	}
	if(Timer==TIM1) 	TIM1->BDTR|=TIM_BDTR_MOE ; 	
}


//Modification of the PWM impulse duration 
void PWM_Modif_Period(TIM_TypeDef *Timer, char channel, float Duration_PWM_us,float Duration_TIM_us){
	
	float Freq_TIM = (1000000./Duration_TIM_us) ; 
	float Freq_PWM = (1000000./Duration_PWM_us) ; 
	
	
	/**
	* CONFIG PWM 
	*/
	u16 arr = Timer->ARR+1;
	float ccr = ((1.)-(Freq_TIM/Freq_PWM))*((float)arr) ;
	if(channel==1) {
		if(Timer->CCR1!=(u16)ccr){
			Timer->CCR1=0;
			Timer->CCR1|=(u16)ccr ; 
		}
	}
	else if (channel==2) {
		if(Timer->CCR2!=(u16)ccr){
			Timer->CCR2=0;
			Timer->CCR2|=(u16)ccr ; 
		}
	}
	else if (channel==3) {	
		if(Timer->CCR3!=(u16)ccr){
			Timer->CCR3=0;
			Timer->CCR3|=(u16)ccr ;
		} 
	}
	else if (channel==4) {
		if(Timer->CCR4!=(u16)ccr){
			Timer->CCR4=0;
			Timer->CCR4|=(u16)ccr ;
		}
	}
}

//launch timer
void Launch_Timer(TIM_TypeDef *Timer) {
	//ENABLE counter 
	Timer->CR1|=TIM_CR1_CEN ; 
}

//Timer initialization in encoder mode
int Init_Tim_Encoder(TIM_TypeDef *Timer, int reset_value){
	
	//channel 1 is linked to Ti1 and channel 2 to Ti2
	Timer->CCMR1|=TIM_CCMR1_CC1S_0;
	Timer->CCMR1&=~TIM_CCMR1_CC1S_1;
	Timer->CCMR1|=TIM_CCMR1_CC2S_0;
	Timer->CCMR1&=~TIM_CCMR1_CC2S_1;
	//Ti2 and Ti1 are not inverted
	Timer->CCER&=~TIM_CCER_CC1P;
	Timer->CCER&=~TIM_CCER_CC2P;
	//counting activation on each channel
	Timer->SMCR|=TIM_SMCR_SMS;
	Timer->SMCR&=~TIM_SMCR_SMS_2;
	Timer->ARR=reset_value-1;
	Timer->CR1|=TIM_CR1_CEN ;
	return 0;
}

//return the timer value
u16 Valeur_Tim(TIM_TypeDef *Timer){
	return Timer->CNT;
}

//reset the timer value
void Reset_Valeur_Tim(TIM_TypeDef *Timer){
	Timer->CNT=0;
}

//timer initialization in input mode 
void init_timer_pwm_input(TIM_TypeDef *Timer, int freq_div){
	
	//upcounting mode 
	Timer->PSC=freq_div-1;
	Timer->ARR=0xFFFF;
	
	TIM4->CCER&=~TIM_CCER_CC1P; //ch1 is none inverted
	TIM4->CCER|=TIM_CCER_CC2P; //ch2 is inverted
	
	//channel 1 and 2 are in input mode and mapped on the same TI (here it's TI1)
	TIM4->CCMR1|=TIM_CCMR1_CC1S_0;
	TIM4->CCMR1|=TIM_CCMR1_CC2S_1;
	
	// reset mode on TI1FP1
	TIM4->SMCR|=TIM_SMCR_TS_2|TIM_SMCR_TS_0|TIM_SMCR_SMS_2;

	//capture compare on channel 1 and 2
	TIM4->CCER|=TIM_CCER_CC1E;
	TIM4->CCER|=TIM_CCER_CC2E;
	
}

//return the capture/compare value of the timer for a given channel
u16 CC_Value( TIM_TypeDef *Timer, int channel){
	if (channel==1){
		return Timer->CCR1 ;}
	else if (channel==2){
		return Timer->CCR2  ;}
	else if (channel==3){
		return Timer->CCR3  ;}
	else {
		return Timer->CCR4  ;}
}




/* ***************
****  IT activation
*/

//overflow IT activation
void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void) ) {
	
	//overflow IT activation 
	Timer->DIER|=TIM_DIER_UIE ; 
	
	if(Timer==TIM2){
		NVIC->IP[28]&=~(0xFF) ; 
		NVIC->IP[28]|=(Priority<<4)  ;  
		ptr_fct_timer=IT_function ; 
		NVIC->ISER[0]|=NVIC_ISER_SETENA_28 ; 
	} 
	else if(Timer==TIM3) {
		NVIC->IP[29]&=~(0xFF) ;
		NVIC->IP[29]|=(Priority<<4) ;
		ptr_fct_timer=IT_function ; 
		NVIC->ISER[0]|=NVIC_ISER_SETENA_29 ; 
	} 
	else if(Timer==TIM4) {
		NVIC->IP[30]&=~(0xFF) ;
		NVIC->IP[30]|=(Priority<<4) ;
		ptr_fct_timer=IT_function ; 
		NVIC->ISER[0]|=NVIC_ISER_SETENA_30 ; 
	}
}

//capture/compare IT activation 
void Timer_Active_IT_CC( TIM_TypeDef *Timer, u8 Priority, int channel, void (*IT_function) (void)) {
	
	if (channel==1){
		Timer->DIER|=TIM_DIER_CC1IE ;}
	else if (channel==2){
		Timer->DIER|=TIM_DIER_CC2IE ;}
	else if (channel==3){
		Timer->DIER|=TIM_DIER_CC3IE ;}
	else if (channel==4){
		Timer->DIER|=TIM_DIER_CC4IE ;}
	
	if(Timer==TIM2){
		NVIC->IP[28]&=~(0xFF) ; 
		NVIC->IP[28]|=(Priority<<4)  ;  
		ptr_fct_timer=IT_function ; 
		NVIC->ISER[0]|=NVIC_ISER_SETENA_28 ; 
	} 
	else if(Timer==TIM3) {
		NVIC->IP[29]&=~(0xFF) ;
		NVIC->IP[29]|=(Priority<<4) ;
		ptr_fct_timer=IT_function ; 
		NVIC->ISER[0]|=NVIC_ISER_SETENA_29 ; 
	} 
	else if(Timer==TIM4) {
		NVIC->IP[30]&=~(0xFF) ;
		NVIC->IP[30]|=(Priority<<4) ;
		ptr_fct_timer=IT_function ; 
		NVIC->ISER[0]|=NVIC_ISER_SETENA_30 ; 
	}
}

