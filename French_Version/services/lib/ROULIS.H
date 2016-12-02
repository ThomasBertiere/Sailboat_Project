


//fonction à appeler quand on passe un angle de 45 degré
void Angle_Depasse() ; 


//initialise le controle du roulis 
void Init_Controle_Roulis() ; 


//initialise la valeur limite de l'angle 
void Init_Angle_Limite(int angle_lim) ; 

//Lance l'acquisition de valeur sur l'ADC
void Controle_Roulis() ;

//Récupère l'angle de la girouette 
void Recup_Angle() ; 

//Variable globale telle que 
//passe à 0 -> angle OK 
//passe à 1 -> angle non OK 
int mode ; 