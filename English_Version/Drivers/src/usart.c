#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef USART
#define USART
#include "usart.h"
#endif



//Usart initialization for emission 
void Init_Usart_Emission(USART_TypeDef *Usart) {
	
	if(Usart==USART1) {
		//Init clock
		RCC->APB2ENR|=RCC_APB2ENR_USART1EN ; 	
	}
	
	//enable USART 
	Usart->CR1|=USART_CR1_UE ; 
		
	//definition of words' length 
	//0 => transmission of 8 bits words 
	Usart->CR1&= ~(USART_CR1_M) ; 
	
	//definition of stop bits number 
	//0 => 1 stop bit 
	Usart->CR2&=~(USART_CR2_STOP) ; 
	
	//baud rate  
	Usart->BRR=0x0342  ; 
	
	//first message transmission
	Usart->CR1|=USART_CR1_TE ; 
	
}

//data transmission (8 bits words)
void Send_Transmission(USART_TypeDef *Usart,char  data) { 
		Usart->DR=(u16)data ; 
}




