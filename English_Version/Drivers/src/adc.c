#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif


//global function pointer for handlers
void (*ptr_fct_adc) (void);

//ADC handlers
void ADC_IRQHandler (void) {
		(*ptr_fct_adc)();
		 //watchdog IT is desactivated
	   if((ADC1->SR & ADC_SR_AWD) == 1){
       ADC1->SR &= ~ADC_SR_AWD;
    }
    if((ADC2->SR & ADC_SR_AWD) == 1){
        ADC2->SR &= ~ADC_SR_AWD;
    }
	//EOC IT is desactivated 
	ADC1->SR&=~ADC_SR_EOC;
	ADC2->SR&=~ADC_SR_EOC;
		
}









//enable ADC's clocks
void ADC_Init_Clock(ADC_TypeDef * Adc){
	
	if (Adc==ADC1) {
		RCC->APB2ENR|=RCC_APB2ENR_ADC1EN ;  
	}
	else if (Adc==ADC2) {
		RCC->APB2ENR|=	RCC_APB2ENR_ADC2EN;  
	}
}
	
//launch ADC acquisition
void ADC_Launch_Acq(ADC_TypeDef * Adc){
	if (Adc==ADC1) {
		ADC1->CR2|=ADC_CR2_ADON; 
	}
	else if (Adc==ADC2) {
		ADC2->CR2|=ADC_CR2_ADON;
	}
}


//ADC initialization
//		- continuous : 0 or 1 => 0 : single mode 1 : continuous mode
//		- sequence_length : 1 to 16
void ADC_init(ADC_TypeDef * Adc,int continuous, int sequence_length){
	
	//single or continuous mode
	if (continuous == 0){
		//cont = 0
		Adc->CR2|=~ADC_CR2_CONT; 
	}
	else if (continuous == 1){
		//cont = 1
		Adc->CR2|=ADC_CR2_CONT; 
	}
	//Determines the number of conversions to be performed (sequence length)
	int seq_l = sequence_length-1;
	Adc->SQR1|=(seq_l<<20);

	//ADC activation
	if (Adc==ADC1) {
		ADC1->CR2|=ADC_CR2_ADON; 
	}
	else if (Adc==ADC2) {
		ADC2->CR2|=ADC_CR2_ADON;
	}
}


//link a channel to a sequence
//		- num_seq : 1 to 16
//		- num_channel : 0 to 17
void ADC_init_sequence_channel(ADC_TypeDef * Adc,int num_seq,int num_channel){
	
	if (num_seq>=1 && num_seq<=6){
		Adc->SQR3&=~(0b1111<<(5*(num_seq-1)));
		Adc->SQR3|=(num_channel<<(5*(num_seq-1)));
	}
	if (num_seq>=7 && num_seq<=12){
		Adc->SQR2&=~(0b1111<<(5*(num_seq-7)));
		Adc->SQR2|=(num_channel<<(5*(num_seq-7)));
	}
	if (num_seq>=13 && num_seq<=16){
		Adc->SQR1&=~(0b1111<<(5*(num_seq-13)));
		Adc->SQR1|=(num_channel<<(5*(num_seq-13)));
	}
	
	//give a sampling time to a channel (we choose the maximum value)
	if(num_channel>=10 && num_channel<=17){
		Adc->SMPR1|=(0x7<<((num_channel-10)*3));
	}
	if(num_channel>=0 && num_channel<=9){
		Adc->SMPR2|=(0x7<<((num_channel)*3));
	}
	
}

// ACD interrupt (IT) initialization 
void Adc_init_IT(ADC_TypeDef * Adc,int priority, void (*fct_IT) (void)){
	
	//IT is linked to the End Of Conversion (EOC)
	if (Adc==ADC1) {
		ADC1->CR1|=ADC_CR1_EOCIE;
	}
	else if (Adc==ADC2) {
		ADC2->CR1|=ADC_CR1_EOCIE;
	}

	ptr_fct_adc=fct_IT;

	NVIC->IP[18]&=~(0xFF) ; 
	NVIC->IP[18]|=(priority<<4)  ; 		
	NVIC->ISER[0]|=NVIC_ISER_SETENA_18 ; 
	
}

//return the ADC value
int Adc_value(ADC_TypeDef * Adc){
	if (Adc==ADC1){
		return (int)(Adc->DR & 0x0000FFFF);
	}
	else {
		return (int)Adc->DR ;
	}

}



/*
* WATCHDOG
*/



void Init_ADC_Watchdog(ADC_TypeDef * Adc,int priority, void (* fct_IT)(void)){ 
  ptr_fct_adc=fct_IT;
  Adc->CR1 |= ADC_CR1_AWDIE;//Enable IT
	NVIC->IP[18]&=~(0xFF) ;
	NVIC->IP[18]|=((priority)<<4);	
	NVIC->ISER[0] |= NVIC_ISER_SETENA_18;
	
}

void ADC_AnalogWatchdogThresholdsConfig (ADC_TypeDef * ADCx, uint16_t HighThreshold, uint16_t LowThreshold){
    
    ADCx->HTR &= ~(ADC_HTR_HT);
    ADCx->HTR |= HighThreshold;
    ADCx->LTR &= ~(ADC_LTR_LT);
		ADCx->LTR |= LowThreshold;
    
}

void ADC_AnalogWatchdogSingleChannelConfig (ADC_TypeDef * ADCx, int ADC_Channel){
    
    ADCx->CR1 |= ADC_CR1_AWDSGL;
    ADCx->CR1 |= ADC_CR1_AWDEN;
		ADCx->CR1 &= ~ADC_CR1_JAWDEN;
    ADCx->CR1 &= ~(ADC_CR1_AWDCH);
    ADCx->CR1 |= ADC_Channel;
	
   
}

void ADC_AnalogWatchdogAllChannelConfig (ADC_TypeDef * ADCx){
    
    ADCx->CR1 &= ~ADC_CR1_AWDSGL;
    ADCx->CR1 |= ADC_CR1_AWDEN;
    ADCx->CR1 &= ~ADC_CR1_JAWDEN;
  
}

