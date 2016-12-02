#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif



//Usart initialization for emission 
void Init_Usart_Emission(USART_TypeDef *Usart);

//data transmission (8 bits words)
void Send_Transmission(USART_TypeDef *Usart,char  data);



