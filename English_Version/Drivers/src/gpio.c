#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef GPIO
#define GPIO
#include "gpio.h"
#endif


//global function pointer for handlers
void (*ptr_fct_gpio) (void);

//external IT handlers
void EXTI0_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//IT desactivation
	EXTI->PR|=EXTI_PR_PR0 ;
}

void EXTI1_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//IT desactivation
	EXTI->PR|=EXTI_PR_PR1;
}

void EXTI2_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//IT desactivation
	EXTI->PR|=EXTI_PR_PR2 ;
}

void EXTI3_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//IT desactivation
	EXTI->PR|=EXTI_PR_PR3;
}

void EXTI4_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//IT desactivation
	EXTI->PR|=EXTI_PR_PR4;
}

void EXTI9_5_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//IT desactivation
	EXTI->PR|=EXTI_PR_PR5 | EXTI_PR_PR6 | EXTI_PR_PR7 |  EXTI_PR_PR8 | EXTI_PR_PR9;
}

void EXTI15_10_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR10 | EXTI_PR_PR11 | EXTI_PR_PR12 |  EXTI_PR_PR13 | EXTI_PR_PR14 | EXTI_PR_PR15 ;
}











//enable GPIO's clocks
void Clock_Init_GPIO(GPIO_TypeDef * Port){

	if (Port==GPIOA){
		RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	}
	else if (Port==GPIOB){
		RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
	}
	else if (Port==GPIOC){
		RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
	}
	else if (Port==GPIOD){
		RCC->APB2ENR|=RCC_APB2ENR_IOPDEN;
	}
}

//enable AFIO's clock
void Clock_Init_AFIO(void){
	RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
}


//Function which configures a GPIO's pin in output mode as following :
	// speed = 1 => output speed = 10 MHz
	// speed = 2 => output speed = 2 MHZ
	// speed = 3 => output speed = 50 MHz
	// mode = 0 => output push pull
	// mode = 1 => output open drain
	// mode = 2 => alternate functiopn push pull 
	// mode = 3 => alternate function open drain
void Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Pin, int speed, int mode ) {
	if ( speed>=1 && speed<=3 ) { 
		if ( mode>=0 && mode<=3) {
			if (Pin<8) {
				Port->CRL&=~(0xf<<(Pin*4));
				Port->CRL|=(speed<<(Pin*4)) | (mode<<((Pin*4)+2) ) ;
			}
			else {
				Port->CRH&=~(0xf<<((Pin%8)*4));
				Port->CRH|=(speed<<((Pin%8)*4)) | ( mode<<(((Pin%8)*4)+2) );

			}
		}
	}
}	

//Function which configures a GPIO's pin in input mode as following :
	// mode = 0 => analog input
	// mode = 1 => floating input
	// mode = 2 => input with pull down / pull up
void Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Pin, int mode ) {
	if ( mode>=0 && mode<=2) {
		if(Pin<8) {
			Port->CRL&=~(0xf<<(Pin*4));
			Port->CRL|=(mode<<((Pin*4)+2)) ; 
		} else {
			Port->CRH&=~(0xf<<((Pin%8)*4));
			Port->CRH|=(mode<<(((Pin%8)*4)+2)) ; 
		}
	}
}

//We put a GPIO's pin to "1"
void Port_IO_Set(GPIO_TypeDef * Port, u8 Pin) {
	Port->BSRR|=(0x01<<Pin)  ; 
}

//We put a GPIO's pin to "0"
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Pin) {
	Port->BSRR|=(0x01<<(Pin+16)) ; 
}

//function which reads a GPIO's pin state
 unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Pin) {
	return ((Port->IDR&(0x01<<Pin))>>Pin)  ; 
}

//GPIO interrupt (IT) initialization
void Init_It_GPIO(GPIO_TypeDef * Port, u8 Pin,int priority, void (*fct_IT) (void) ){
	
	ptr_fct_gpio=fct_IT;
	//AFIO's clock activation
	RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
	
	//interrupt mapping
	EXTI->IMR|=(EXTI_IMR_MR0<<Pin);

	//IT is on rising edge
	EXTI->RTSR|=(EXTI_RTSR_TR0<<Pin);
	
	//external interupts configuration => a GPIO pin is linked to an IT 
	if (Port==GPIOA) {
		if (Pin>=0 && Pin<=3){
			AFIO->EXTICR[0]|=(0<<(Pin*4));
		}
		else if (Pin>=4 && Pin<=7){
			AFIO->EXTICR[1]|=(0<<((Pin-4)*4));
		}
		else if (Pin>=8 && Pin<=11){
			AFIO->EXTICR[2]|=(0<<((Pin-8)*4));
		}
		else if (Pin>=12 && Pin<=15){
			AFIO->EXTICR[3]|=(0<<((Pin-12)*4));
		}
	}
	if (Port==GPIOB) {
		if (Pin>=0 && Pin<=3){
			AFIO->EXTICR[0]|=(1<<(Pin*4));
		}
		else if (Pin>=4 && Pin<=7){
			AFIO->EXTICR[1]|=(1<<((Pin-4)*4));
		}
		else if (Pin>=8 && Pin<=11){
			AFIO->EXTICR[2]|=(1<<((Pin-8)*4));
		}
		else if (Pin>=12 && Pin<=15){
			AFIO->EXTICR[3]|=(1<<((Pin-12)*4));
		}
	}
	if (Port==GPIOC) {
		if (Pin>=0 && Pin<=3){
			AFIO->EXTICR[0]|=(2<<(Pin*4));
		}
		else if (Pin>=4 && Pin<=7){
			AFIO->EXTICR[1]|=(2<<((Pin-4)*4));
		}
		else if (Pin>=8 && Pin<=11){
			AFIO->EXTICR[2]|=(2<<((Pin-8)*4));
		}
		else if (Pin>=12 && Pin<=15){
			AFIO->EXTICR[3]|=(2<<((Pin-12)*4));
		}
	}
	if (Port==GPIOD) {
		if (Pin>=0 && Pin<=3){
			AFIO->EXTICR[0]|=(3<<(Pin*4));
		}
		else if (Pin>=4 && Pin<=7){
			AFIO->EXTICR[1]|=(3<<((Pin-4)*4));
		}
		else if (Pin>=8 && Pin<=11){
			AFIO->EXTICR[2]|=(3<<((Pin-8)*4));
		}
		else if (Pin>=12 && Pin<=15){
			AFIO->EXTICR[3]|=(3<<((Pin-12)*4));
		}
	}
	
	// IT activation in the NVIC
	if (Pin==0){
		NVIC->IP[6]&=~(0xFF) ; 
		NVIC->IP[6]|=(priority<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_6 ; 
	}
	else if (Pin==1){
		NVIC->IP[7]&=~(0xFF) ; 
		NVIC->IP[7]|=(priority<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_7 ; 	
	}
	else if (Pin==2){
		NVIC->IP[8]&=~(0xFF) ; 
		NVIC->IP[8]|=(priority<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_8 ; 		
	}
	else if (Pin==3){
		NVIC->IP[9]&=~(0xFF) ; 
		NVIC->IP[9]|=(priority<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_9 ; 		
	}
	else if (Pin==4){
		NVIC->IP[10]&=~(0xFF) ; 
		NVIC->IP[10]|=(priority<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_10 ; 		
	}
	else if (Pin>=5 && Pin<=9){
		NVIC->IP[23]&=~(0xFF) ; 
		NVIC->IP[23]|=(priority<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_23 ; 		
	}
	else if (Pin>=10 && Pin<=15){
		NVIC->IP[40]&=~(0xFF) ; 
		NVIC->IP[40]|=(priority<<4)  ; 		
		NVIC->ISER[1]|=NVIC_ISER_SETENA_8 ; 		
	}
	
}

