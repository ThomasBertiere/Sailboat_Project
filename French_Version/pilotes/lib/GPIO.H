#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif



//Fonction qui enable la clock des GPIOs
void Clock_Init_GPIO(GPIO_TypeDef * Port);

//Fonction qui enable la clock de l'AFIO
void Clock_Init_AFIO(void);

//Fonction qui permet de configurer une broche d'un port en :
	// speed = 1 => output speed = 10 MHz
	// speed = 2 => output speed = 2 MHZ
	// speed = 3 => output speed = 50 MHz
	// mode = 0 => output push pull
	// mode = 1 => output open drain
	// mode = 2 => alternate functiopn push pull 
	// mode = 3 => alternate function open drain
void Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche, int speed, int mode) ; 

// fonction qui permet de configurer une broche d'un port en input :
	// mode = 0 => analog input
	// mode = 1 => floating input
	// mode = 2 => input with pull down / pull up
void Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche, int mode) ; 

//fonction qui permet de mettre à 1 une broche d'un port
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche) ; 

//fonction qui permet de mettre à 0 une broche d'un port
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche) ; 

//fonction qui permet de lire l'état d'une broche d'un port
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) ; 

//fonction qui permet d'associé une IT à une broche d'un GPIO
void Init_It_GPIO(GPIO_TypeDef * Port, u8 Broche,int priorite, void (*fct_IT) (void) );
