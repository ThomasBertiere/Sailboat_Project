#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef GPIO
#define GPIO
#include "gpio.h"
#endif


//pointeur de fonction global pour les handlers
void (*ptr_fct_gpio) (void);




//Fonction qui enable la clock des GPIOs
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

//Fonction qui enable la clock de l'AFIO
void Clock_Init_AFIO(void){
	RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
}


//Fonction qui permet de configurer une broche d'un port en :
	// speed = 1 => output speed = 10 MHz
	// speed = 2 => output speed = 2 MHZ
	// speed = 3 => output speed = 50 MHz
	// mode = 0 => output push pull
	// mode = 1 => output open drain
	// mode = 2 => alternate functiopn push pull 
	// mode = 3 => alternate function open drain
void Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche, int speed, int mode ) {
	if ( speed>=1 && speed<=3 ) { 
		if ( mode>=0 && mode<=3) {
			if (Broche<8) {
				Port->CRL&=~(0xf<<(Broche*4));
				Port->CRL|=(speed<<(Broche*4)) | (mode<<((Broche*4)+2) ) ;
			}
			else {
				Port->CRH&=~(0xf<<((Broche%8)*4));
				Port->CRH|=(speed<<((Broche%8)*4)) | ( mode<<(((Broche%8)*4)+2) );

			}
		}
	}
}	






// fonction qui permet de configurer une broche d'un port en input :
	// mode = 0 => analog input
	// mode = 1 => floating input
	// mode = 2 => input with pull down / pull up
void Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche, int mode ) {
	if ( mode>=0 && mode<=2) {
		if(Broche<8) {
			Port->CRL&=~(0xf<<(Broche*4));
			Port->CRL|=(mode<<((Broche*4)+2)) ; 
		} else {
			Port->CRH&=~(0xf<<((Broche%8)*4));
			Port->CRH|=(mode<<(((Broche%8)*4)+2)) ; 
		}
	}
}






//fonction qui permet de mettre à 1 une broche d'un port
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche) {
	Port->BSRR|=(0x01<<Broche)  ; 
}






//fonction qui permet de mettre à 0 une broche d'un port
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche) {
	Port->BSRR|=(0x01<<(Broche+16)) ; 
}





//fonction qui permet de lire l'état d'une broche d'un port
 unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) {
	return ((Port->IDR&(0x01<<Broche))>>Broche)  ; 
}







//fonction qui permet d'associé une IT à une broche d'un GPIO
void Init_It_GPIO(GPIO_TypeDef * Port, u8 Broche,int priorite, void (*fct_IT) (void) ){
	
	ptr_fct_gpio=fct_IT;
	//activation de la clock pour le AFIO (Alternate Function Input/Output)
	RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
	
	//masquage de l'IT
	EXTI->IMR|=(EXTI_IMR_MR0<<Broche);

	//L'IT est sur front montant 
	EXTI->RTSR|=(EXTI_RTSR_TR0<<Broche);
	
	//configuration des external interupts => association d'une broche d'un GPIO à une IT
	if (Port==GPIOA) {
		if (Broche>=0 && Broche<=3){
			AFIO->EXTICR[0]|=(0<<(Broche*4));
		}
		else if (Broche>=4 && Broche<=7){
			AFIO->EXTICR[1]|=(0<<((Broche-4)*4));
		}
		else if (Broche>=8 && Broche<=11){
			AFIO->EXTICR[2]|=(0<<((Broche-8)*4));
		}
		else if (Broche>=12 && Broche<=15){
			AFIO->EXTICR[3]|=(0<<((Broche-12)*4));
		}
	}
	if (Port==GPIOB) {
		if (Broche>=0 && Broche<=3){
			AFIO->EXTICR[0]|=(1<<(Broche*4));
		}
		else if (Broche>=4 && Broche<=7){
			AFIO->EXTICR[1]|=(1<<((Broche-4)*4));
		}
		else if (Broche>=8 && Broche<=11){
			AFIO->EXTICR[2]|=(1<<((Broche-8)*4));
		}
		else if (Broche>=12 && Broche<=15){
			AFIO->EXTICR[3]|=(1<<((Broche-12)*4));
		}
	}
	if (Port==GPIOC) {
		if (Broche>=0 && Broche<=3){
			AFIO->EXTICR[0]|=(2<<(Broche*4));
		}
		else if (Broche>=4 && Broche<=7){
			AFIO->EXTICR[1]|=(2<<((Broche-4)*4));
		}
		else if (Broche>=8 && Broche<=11){
			AFIO->EXTICR[2]|=(2<<((Broche-8)*4));
		}
		else if (Broche>=12 && Broche<=15){
			AFIO->EXTICR[3]|=(2<<((Broche-12)*4));
		}
	}
	if (Port==GPIOD) {
		if (Broche>=0 && Broche<=3){
			AFIO->EXTICR[0]|=(3<<(Broche*4));
		}
		else if (Broche>=4 && Broche<=7){
			AFIO->EXTICR[1]|=(3<<((Broche-4)*4));
		}
		else if (Broche>=8 && Broche<=11){
			AFIO->EXTICR[2]|=(3<<((Broche-8)*4));
		}
		else if (Broche>=12 && Broche<=15){
			AFIO->EXTICR[3]|=(3<<((Broche-12)*4));
		}
	}
	
	//activation de l'IT au sein du NVIC
	if (Broche==0){
		NVIC->IP[6]&=~(0xFF) ; 
		NVIC->IP[6]|=(priorite<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_6 ; 
	}
	else if (Broche==1){
		NVIC->IP[7]&=~(0xFF) ; 
		NVIC->IP[7]|=(priorite<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_7 ; 	
	}
	else if (Broche==2){
		NVIC->IP[8]&=~(0xFF) ; 
		NVIC->IP[8]|=(priorite<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_8 ; 		
	}
	else if (Broche==3){
		NVIC->IP[9]&=~(0xFF) ; 
		NVIC->IP[9]|=(priorite<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_9 ; 		
	}
	else if (Broche==4){
		NVIC->IP[10]&=~(0xFF) ; 
		NVIC->IP[10]|=(priorite<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_10 ; 		
	}
	else if (Broche>=5 && Broche<=9){
		NVIC->IP[23]&=~(0xFF) ; 
		NVIC->IP[23]|=(priorite<<4)  ; 		
		NVIC->ISER[0]|=NVIC_ISER_SETENA_23 ; 		
	}
	else if (Broche>=10 && Broche<=15){
		NVIC->IP[40]&=~(0xFF) ; 
		NVIC->IP[40]|=(priorite<<4)  ; 		
		NVIC->ISER[1]|=NVIC_ISER_SETENA_8 ; 		
	}
	
}



//handler des external IT
void EXTI0_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR0 ;
}

void EXTI1_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR1;
}

void EXTI2_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR2 ;
}

void EXTI3_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR3;
}

void EXTI4_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR4;
}

void EXTI9_5_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR5 | EXTI_PR_PR6 | EXTI_PR_PR7 |  EXTI_PR_PR8 | EXTI_PR_PR9;
}

void EXTI15_10_IRQHandler (void) {
	(*ptr_fct_gpio)();
	//désactive l'IT
	EXTI->PR|=EXTI_PR_PR10 | EXTI_PR_PR11 | EXTI_PR_PR12 |  EXTI_PR_PR13 | EXTI_PR_PR14 | EXTI_PR_PR15 ;
}

