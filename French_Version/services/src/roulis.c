#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif

#ifndef ROULIS
#define ROULIS
#include "roulis.h"
#endif 





//fonction à appeler quand on passe un angle de 45 degré 
void Angle_Depasse()  {
	/* ----------A FAIRE------------
	-- ENVOIE MESSAGE USART (LES MESSAGES USART SONT ENVOYES DANS LE WHILE(1) DU MAIN CAR LONG A ENVOYER)
	-- ARRETER LE BORDAGE DE VOILE 
	*/
	mode=1 ; 
}



/*ATTENTION SEUIL HAUT ET BAS A MODIFIER EN FONCTION DES VOILIERS*/
void Recup_Angle() {
	int val = Adc_recup_valeur(ADC1); 
	
	//seuil haut et bas à modifier en fonction des voiliers 
	int seuilBas = 1400 ; 
	int seuilHaut = 2060 ; 
	
	if((val<seuilBas)||(val>seuilHaut)) {
		if(!mode) 
		{	Angle_Depasse() ; }
	} else if(mode) { 
			mode=0  ;
	}
}


//initialise le controle du roulis  //SEQUENCE=1 ???? // MODIF a faire sur BATTERIE ???
void Init_Controle_Roulis() {
	ADC_Init_Clock(ADC1);
	ADC_init(ADC1,1,1);
	ADC_init_sequence_channel(ADC1,1,10);
}	

void Controle_Roulis() {
	ADC_Launch_Acq(ADC1);
}



