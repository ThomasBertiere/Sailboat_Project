


//fonction � appeler quand on passe un angle de 45 degr�
void Angle_Depasse() ; 


//initialise le controle du roulis 
void Init_Controle_Roulis() ; 


//initialise la valeur limite de l'angle 
void Init_Angle_Limite(int angle_lim) ; 

//Lance l'acquisition de valeur sur l'ADC
void Controle_Roulis() ;

//R�cup�re l'angle de la girouette 
void Recup_Angle() ; 

//Variable globale telle que 
//passe � 0 -> angle OK 
//passe � 1 -> angle non OK 
int mode ; 