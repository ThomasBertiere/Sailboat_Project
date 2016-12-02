#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif



//enable GPIO's clocks
void Clock_Init_GPIO(GPIO_TypeDef * Port);

//enable AFIO's clock
void Clock_Init_AFIO(void);

//Function which configures a GPIO's pin in output mode as following :
	// speed = 1 => output speed = 10 MHz
	// speed = 2 => output speed = 2 MHZ
	// speed = 3 => output speed = 50 MHz
	// mode = 0 => output push pull
	// mode = 1 => output open drain
	// mode = 2 => alternate functiopn push pull 
	// mode = 3 => alternate function open drain
void Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Pin, int speed, int mode ) ; 

//Function which configures a GPIO's pin in input mode as following :
	// mode = 0 => analog input
	// mode = 1 => floating input
	// mode = 2 => input with pull down / pull up
void Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Pin, int mode ); 

///We put a GPIO's pin to "1"
void Port_IO_Set(GPIO_TypeDef * Port, u8 Pin); 

//We put a GPIO's pin to "0"
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Pin); 

//function which reads a GPIO's pin state
 unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Pin) ; 

//GPIO interrupt (IT) initialization
void Init_It_GPIO(GPIO_TypeDef * Port, u8 Pin,int priority, void (*fct_IT) (void) );
