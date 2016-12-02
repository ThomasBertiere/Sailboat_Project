#ifndef STM32
#define STM32
#include "stm32f10x.h"
#endif

//initialise la girouette
void init_girouette();

//retourne l'angle du vent 
u16 angle_vent();

//reset la girouette
void reset_girouette() ; 
