#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif




//Initialisation usart pour emission 
void Init_Usart_Emission(USART_TypeDef *Usart) ; 

//envoie de donn�es 
//attention data doit avoir une longueur de 8 bits 
//sinon donn�es perdues 
void Send_Transmission(USART_TypeDef *Usart,char data) ; 






