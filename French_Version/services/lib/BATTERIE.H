#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

#ifndef ADC
#define ADC
#include "adc.h"
#endif


//initailise le controleur de la batterie. Permet de connaitre la charge de la batterie
void init_controleur_batterie();

//renvoie la charge de la batterie
int charge_batterie();

//fonction permettant d'associé une charge limite à la batterie. Val_limite est en V.
void init_charge_limite(int val_limite);
	
//variable globale mise à 1 quand la batterie passe sous un certain seuil 
int stop ; 
