#include <SimpleTimer.h>
#define _DEBUG true
SimpleTimer timer; // Timer pour ?chantillonnage



String DistanceDegres;
int cptcarac=0;
long derniercgtcompteur=0;
int transfert=1;
String usbrecue="";
String A="A";
byte ch;
String degresrecus;
String distancerecue;

float calculTempo;
float time=0;

//MOTOR
//int IN1=2;

int IN1= 28;  
//7; shield

int IN2=26;
//int MotorD=3;

int MotorG = 5; 
//=5;

//int IN3=7;

int IN3 = 24;
//=4;

int IN4=22;
//int MotorG=5;

int MotorD =3;
//=6;
int stop=0;
int trig = 12; 
int echo = 11; 
long lecture_echo; 
long cm;
float bilup,biluplup,botch;
int tourner=0;
int avancer=0;
int reculer=0;
int TournerGauche=0;
int TournerDroite=0;
int first=1;
//CODOR
long CodeurG=0;
long CodeurG2=0;
long CodeurD=0;
int CodeurParalleleG=0;
int CodeurParalleleD=0;
long TotalCodeurG=0;
unsigned TotalCodeurD=0;
long TempoCodeur=0;
long TempoCodeurPrec=0;
const byte encoder0pinA = 21;//A pin -> the interrupt pin 2
const byte encoder0pinB = 4;//B pin -> the digital pin 4
const byte encoder1pinA = 20;//A pin -> the interrupt pin 2
const byte encoder1pinB = 10;//B pin -> the digital pin 4
byte encoder0PinALast;
byte encoder1PinALast;
boolean DirectionD;//the rotation direction
boolean DirectionG;//the rotation direction
//FRECATOR
const int frequence_echantillonnage =50;  // Fr?quence d'ex?cution de l'asservissement
const int rapport_reducteur = 51;          // Rapport entre le nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 26;      // Nombre de tick codeuse par tour de l'arbre moteur
 
//COMANDOR
float rotationdegres = 0;
 int distancecm=0;
 float diamrouecm=11.45;
 float distancerouecm = 30.75; 
float CMG = 1;
float CMD = 1;//  Nombre de tours de roue par seconde
float consigne_moteur_nombre_tours_par_secondeG = 0; //variable nbre tour/sec
float consigne_moteur_nombre_tours_par_secondeD = 0; //variable nbre tour/sec
//ASSERVISSOR
int cmdG = 0;      
int cmdD = 0;                    // Commande du moteur
float erreur_precedenteG = consigne_moteur_nombre_tours_par_secondeG;
float erreur_precedenteD = consigne_moteur_nombre_tours_par_secondeD;
float somme_erreurG = 0;   // Somme des erreurs pour l'int?grateur
float somme_erreurD = 0;   // Somme des erreurs pour l'int?grateur
float kp = 235;           // Coefficient proportionnel
float ki = 12;           // Coefficient int?grateur
float kd = 50;           // Coefficient d?rivateur
float kpG = 235;           // Coefficient proportionnel
float kiG = 12;           // Coefficient int?grateur
float kdG = 50;           // Coefficient d?rivateur
//ASSERVISSOR PARALLELOR
float cmdParallele = 0;           
int erreurParallele;
int erreur_precedenteParallele = 0;
int somme_erreurParallele = 0;   // Somme des erreurs pour l'int?grateur

float kpp =0.02;           // Coefficient proportionnel
float kii =  0.0;           // Coefficient int?grateur
float kdd = 0.0;           // Coefficient d?rivateur


 float timef, timef2;
/* Routine d'initialisation */

void setup() 
{
         EncoderInit();//Initialize the module
	Serial.begin(115200);   // Initialisation port COM
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);
	pinMode(MotorD,OUTPUT);
	pinMode(MotorG,OUTPUT);
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(MotorD,0);  // Sortie moteur ? 0
	analogWrite(MotorG,0);  // Sortie moteur ? 0
	                // Pause de 5 sec pour laisser le temps au 	moteur de s'arr?ter si celui-ci est en marche
	
 	timer.setInterval(1000/frequence_echantillonnage, asservissement); //interrupt pour PID et asservissement
        timer.setInterval(1000/frequence_echantillonnage, Avancer);
         //timer.setInterval(1000, Obstacle);
          timer.setInterval(100, tempo);
         // timer.setInterval(20,parallelisme);
        timer.setInterval(1000/frequence_echantillonnage, Tourner);
          pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(115200); 
  stop=1;
}
void EncoderInit()
{
  DirectionD = false;//default -> Forward 
    DirectionG = true;//default -> Forward 
  pinMode(encoder0pinB,INPUT);  
    pinMode(encoder1pinB,INPUT); 
  attachInterrupt(2, RwheelSpeed, CHANGE);//int.0 
    attachInterrupt(3, LwheelSpeed, CHANGE);//int.0 
}
void parallelisme()
{
        erreurParallele=CodeurParalleleD-CodeurParalleleG;
	CodeurParalleleG=0;
	CodeurParalleleD=0;
	// Calcul de l'erreur

	somme_erreurParallele += erreurParallele;
	float delta_erreurParallele = erreurParallele-erreur_precedenteParallele;
	erreur_precedenteParallele = erreurParallele;


	// PID : calcul de la commande
	cmdParallele = kpp*erreurParallele + kii*somme_erreurParallele + kdd*delta_erreurParallele;
}

void RwheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && DirectionD)
    {
      DirectionD = true; //Reverse
    }
    else if(val == HIGH && !DirectionD)
    {
      DirectionD = false;  //Forward
    }
  }
  encoder0PinALast = Lstate;
   
  if(!DirectionD)
  {
  CodeurD++;
  TotalCodeurD++;
  }
  else
  {
  CodeurD--;
  TotalCodeurD--;
  }
}
void LwheelSpeed()
{
  int Lstate = digitalRead(encoder1pinA);
  if((encoder1PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder1pinB);
    if(val == LOW && DirectionG)
    {
      DirectionG = true; //Reverse
    }
    else if(val == HIGH && !DirectionG)
    {
      DirectionG = false;  //Forward
    }
  }
  encoder1PinALast = Lstate;
   
  if(!DirectionG)
  {
    CodeurG++;
    TotalCodeurG++;
  }
  else
  {
    CodeurG++;
    TotalCodeurG++;
   }
}
void tempo()
{
time++;
if (avancer==1)
{
  TempoCodeur=(TotalCodeurG+TotalCodeurD)-TempoCodeurPrec;
  TempoCodeurPrec=TotalCodeurG+TotalCodeurD;
 Serial.print((TempoCodeur*diamrouecm*314)/(4*rapport_reducteur*tick_par_tour_codeuse));
 Serial.print(";");
 Serial.println("0");
}
else
{
  if (TournerGauche==1)
  {
    TempoCodeur=(TotalCodeurG+TotalCodeurD)-TempoCodeurPrec;
  TempoCodeurPrec=TotalCodeurG+TotalCodeurD;
  calculTempo=((TempoCodeur*diamrouecm*3.14)/(4*rapport_reducteur*tick_par_tour_codeuse))/(distancerouecm*3.14);
     Serial.print("0");
     Serial.print(";-");
     Serial.println(calculTempo);
  }
    if (TournerDroite==1)
  {
    TempoCodeur=(TotalCodeurG+TotalCodeurD)-TempoCodeurPrec;
  TempoCodeurPrec=TotalCodeurG+TotalCodeurD;
  calculTempo=((TempoCodeur*diamrouecm*3.14)/(4*rapport_reducteur*tick_par_tour_codeuse))/(distancerouecm*3.14);
     Serial.print("0");
     Serial.print(";");
     Serial.println(calculTempo);
  }
}
}

  
/* Interruption pour calcul du PID */
void asservissement()
{
      
    if (stop==0)
    {
 
	// R?initialisation du nombre de tick de la codeuse
	int ValCodeurG=CodeurG;
	int ValCodeurD=CodeurD;
	TotalCodeurG+=CodeurG;
	TotalCodeurD+=CodeurD;
	CodeurG=0;
	CodeurD=0;
	// Calcul de l'erreur
	int frequence_codeuseG = frequence_echantillonnage*ValCodeurG;
	int frequence_codeuseD = frequence_echantillonnage*ValCodeurD;
	float nb_tour_par_secG = (float)frequence_codeuseG/(float)tick_par_tour_codeuse/(float)rapport_reducteur;
	float nb_tour_par_secD = (float)frequence_codeuseD/(float)tick_par_tour_codeuse/(float)rapport_reducteur;
	float erreurG = consigne_moteur_nombre_tours_par_secondeG - nb_tour_par_secG;
	float erreurD = consigne_moteur_nombre_tours_par_secondeD - nb_tour_par_secD;
	somme_erreurG += erreurG;
	somme_erreurD += erreurD;
	float delta_erreurG = erreurG-erreur_precedenteG;
	float delta_erreurD = erreurD-erreur_precedenteD;

 	erreur_precedenteG = erreurG;
	erreur_precedenteD = erreurD;
	// PID : calcul de la commande
	cmdG = kp*erreurG + ki*somme_erreurG + kd*delta_erreurG;
	cmdD = kp*erreurD + ki*somme_erreurD + kd*delta_erreurD;

        //cmdG=100;
        //cmdD=100;
	// Normalisation et contr?le du moteur

	if(cmdG < 0) cmdG=0;
	if(cmdG > 255) cmdG = 255;
	//analogWrite(MotorG,cmdG);
	if(cmdD < 0) cmdD=0;
	if(cmdD>255) cmdD = 255;
	analogWrite(MotorD, cmdD);
        analogWrite(MotorG, cmdG);

    // DEBUG
     bilup=(TotalCodeurG)*diamrouecm*3.14/(2*rapport_reducteur*tick_par_tour_codeuse);
     biluplup= (TotalCodeurD)*diamrouecm*3.14/(2*rapport_reducteur*tick_par_tour_codeuse);

  
    }
}
/*Fontion Avancer */
void Avancer ()
{
if ( (avancer==1)  || (reculer==1) )
{  
  
if (( ((TotalCodeurG+TotalCodeurD)*diamrouecm*3.14)/(4*rapport_reducteur*tick_par_tour_codeuse) >= distancecm ) && (tourner==0))
{

      
      stop=1;
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
       // cmdD=255;
          
     consigne_moteur_nombre_tours_par_secondeG=0;
      consigne_moteur_nombre_tours_par_secondeD=0;
     cmdG=0;
     cmdD=0;
     analogWrite(MotorD, cmdD);
     analogWrite(MotorG, cmdG);
     distancecm=0;
     //TotalCodeurG=0;
     //TotalCodeurD=0;
     TotalCodeurG=0;
     TotalCodeurD=0;
     avancer=0;
     reculer=0;
     time=0;
      // delay(2000); 
   //  digitalWrite(IN1,HIGH);
    // digitalWrite(IN2,LOW); 

}  
else
{
  if (avancer==1)
  {
      digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
  }
  else if (reculer==1)
  {
     digitalWrite(IN1,LOW);
          digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
  }
  if((distancecm/(3.14*diamrouecm))<1)
  {
  botch=sqrt((distancecm)/(diamrouecm*3.14/4));
 if (time<(botch*5) )
 {
 float timef = (float) time; 
 consigne_moteur_nombre_tours_par_secondeG= 0.1*(timef+cmdParallele);
 consigne_moteur_nombre_tours_par_secondeD=0.1*(timef-cmdParallele);
 }
 else
 {
 timef2= (float) time;
 consigne_moteur_nombre_tours_par_secondeG= botch-( 0.1*((timef2-timef)+cmdParallele) );
 consigne_moteur_nombre_tours_par_secondeD = botch-( 0.1*((timef2-timef)-cmdParallele) );
  if  ((consigne_moteur_nombre_tours_par_secondeG<0.05)||(consigne_moteur_nombre_tours_par_secondeD<0.05))
  {
  distancecm=0;
  }
  }
  }
  else
  {
    if (time<10 )
    {
     float timef = (float) time; 
    consigne_moteur_nombre_tours_par_secondeG= 0.1*(timef+cmdParallele);
    consigne_moteur_nombre_tours_par_secondeD=0.1*(timef-cmdParallele);
    }
  
    else if (   (TotalCodeurG+TotalCodeurD)*diamrouecm*3.14  /  (4*rapport_reducteur*tick_par_tour_codeuse)<= distancecm-20 )
    
    {
    consigne_moteur_nombre_tours_par_secondeG=CMG+cmdParallele;
    consigne_moteur_nombre_tours_par_secondeD=CMD-cmdParallele;
    timef= (float) time;
    }
    else
    {
      timef2= (float) time;
      consigne_moteur_nombre_tours_par_secondeG= CMG-( 0.1*((timef2-timef)+cmdParallele) );
      consigne_moteur_nombre_tours_par_secondeD = CMD-( 0.1*((timef2-timef)-cmdParallele) );
      if  ((consigne_moteur_nombre_tours_par_secondeG<0.05)||(consigne_moteur_nombre_tours_par_secondeD<0.05))
      {
        distancecm=0;
      }
    }
  }
}  

}

}


void Obstacle ()
{
         
  digitalWrite(trig, HIGH); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 
  Serial.println (cm);
  if (cm<15)
 {
    stop=1;
   CMG=0;
   CMD=0;
       cmdG=0;
     cmdD=0;
     	analogWrite(MotorD, cmdD);
        analogWrite(MotorG, cmdG);
        stop=1;
     Serial.println ("Obstacle");

 }   
}  

void Tourner ()
{
if ((TournerGauche==1)||(TournerDroite==1))
{  
float pourtour=rotationdegres/360;
if ( (((TotalCodeurG+TotalCodeurD)*diamrouecm*3.14)/(4*rapport_reducteur*tick_par_tour_codeuse)) >= ((rotationdegres/360)*distancerouecm*3.14) )
{
     //Serial.println(pourtour);
    consigne_moteur_nombre_tours_par_secondeG=0;
      consigne_moteur_nombre_tours_par_secondeD=0;
     cmdG=0;
     cmdD=0;
     analogWrite(MotorD, cmdD);
     analogWrite(MotorG, cmdG);
  rotationdegres=0;
  TotalCodeurG=0;
  TotalCodeurD=0;
  if (TournerGauche==1)
  {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  }
  else if (TournerDroite==1)
  {
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
  }
  stop=1;
  TournerGauche=0;
  TournerDroite=0;
  time=0;
  
  
}  
else
{
  if (TournerGauche==1)
  {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH); 
  }
  else if (TournerDroite==1)
  {
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
  }
   distancecm=(rotationdegres/360)*distancerouecm*3.14;
   if((distancecm/(3.14*diamrouecm))<1)
  {
  botch=sqrt((distancecm)/(diamrouecm*3.14/4));
 if (time<(botch*5) )
 {
 float timef = (float) time; 
 consigne_moteur_nombre_tours_par_secondeG= 0.1*(timef+cmdParallele);
 consigne_moteur_nombre_tours_par_secondeD=0.1*(timef-cmdParallele);
 }
 else
 {
 timef2= (float) time;
 consigne_moteur_nombre_tours_par_secondeG= botch-( 0.1*((timef2-timef)+cmdParallele) );
 consigne_moteur_nombre_tours_par_secondeD = botch-( 0.1*((timef2-timef)-cmdParallele) );
  if  ((consigne_moteur_nombre_tours_par_secondeG<0.05)||(consigne_moteur_nombre_tours_par_secondeD<0.05))
  {
  rotationdegres=0;
  }
  }
  }
  else
  {
    if (time<10 )
    {
     float timef = (float) time; 
    consigne_moteur_nombre_tours_par_secondeG= 0.1*(timef+cmdParallele);
    consigne_moteur_nombre_tours_par_secondeD=0.1*(timef-cmdParallele);
    }
  
    else if (   (TotalCodeurG+TotalCodeurD)*diamrouecm*3.14  /  (4*rapport_reducteur*tick_par_tour_codeuse)<= distancecm-20 )
    
    {
    consigne_moteur_nombre_tours_par_secondeG=CMG+cmdParallele;
    consigne_moteur_nombre_tours_par_secondeD=CMD-cmdParallele;
    timef= (float) time;
    }
    else
    {
      timef2= (float) time;
      consigne_moteur_nombre_tours_par_secondeG= CMG-( 1*((timef2-timef)+cmdParallele) );
      consigne_moteur_nombre_tours_par_secondeD = CMD-( 1*((timef2-timef)-cmdParallele) );
      if  ((consigne_moteur_nombre_tours_par_secondeG<0.05)||(consigne_moteur_nombre_tours_par_secondeD<0.05))
      {
        rotationdegres=0;
      }
    }
  }





              
}
}
}  
  
/* Fonction principale */
void loop()
{

      timer.run();

    if ((cptcarac==0)&&(Serial.available()))
  {
    ch=Serial.read();
    usbrecue=usbrecue+char(ch);
    if (usbrecue=="A")
    {
      if (stop==1)
      {
      distancecm=(distancerecue.toInt());
      avancer=1;
      cptcarac=0;
      usbrecue="";
      time=0;
      stop=0;
      }
      
    } 
     else if (usbrecue=="R")
    {
       if (stop==1)
      {
      distancecm=(distancerecue.toInt());
      reculer=1;
      cptcarac=0;
      usbrecue="";
      time=0;
      stop=0;
      }
 
    }
    else if (usbrecue=="G")
    {
       if (stop==1)
      {
      rotationdegres=(degresrecus.toInt());
      //Serial.println(rotationdegres);
      TournerGauche=1;
      cptcarac=0;
      usbrecue="";
      time=0;
      stop=0;
      }
 
      
    }
    else if (usbrecue=="D")
    {
       if (stop==1)
      {
      rotationdegres=(degresrecus.toInt());
      TournerDroite=1;
      cptcarac=0;
      usbrecue="";
      time=0;
      stop=0;
      }
       
    }
    else if (usbrecue=="S")
    {
      distancecm=0;
      rotationdegres=0;
      stop=1;
     analogWrite(MotorD, 0);
     analogWrite(MotorG, 0);
      cptcarac=0;
      usbrecue=""; 
    }
    else if ((usbrecue=="i")||(usbrecue=="d"))
    {
    usbrecue="";
    DistanceDegres+=(char)ch;
    cptcarac++;
    }
    else
    {
      usbrecue="";
    }
  }
  else
  {

    if (Serial.available())
    {
      ch=Serial.read();
      usbrecue=usbrecue+(char)ch;
      cptcarac++;
    }
 
    if ((cptcarac==4)&&(!Serial.available()))
    {
      if (DistanceDegres=="i")
      {
      distancerecue=usbrecue;
      DistanceDegres="";
      }
      else if (DistanceDegres=="d")
      {
        degresrecus=usbrecue;
        DistanceDegres="";
        
      }
      cptcarac=0;
      usbrecue="";
    }
    
    
  }


} 




