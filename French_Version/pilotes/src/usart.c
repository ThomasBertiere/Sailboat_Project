#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef USART
#define USART
#include "usart.h"
#endif



//Initialisation usart pour emission 
void Init_Usart_Emission(USART_TypeDef *Usart) {
	
	if(Usart==USART1) {
		//Init clock
		RCC->APB2ENR|=RCC_APB2ENR_USART1EN ; 	
	}
	
	
	//enable USART 
	Usart->CR1|=USART_CR1_UE ; 
		
	//definition longueur des mots à transmetre 
	//bit à zéro => transmission de mots de 8bits 
	Usart->CR1&= ~(USART_CR1_M) ; 
	
	//definition du nombre de bits stop 
	//bit à zéro => 1 seul bit de STOP 
	Usart->CR2&=~(USART_CR2_STOP) ; 
	
	//-----A FAIRE-----
	//definir le baud rate 
	//REMPLACER LE 0 
	Usart->BRR=0x0342  ; 
	
	//envoie de la première transmission 
	Usart->CR1|=USART_CR1_TE ; 
	
}

//envoie de données 
//attention data doit avoir une longueur de 8 bits 
//sinon données perdues 
void Send_Transmission(USART_TypeDef *Usart,char  data) {
		//ecriture data dans le registre DR 
		Usart->DR=(u16)data ; 
}




