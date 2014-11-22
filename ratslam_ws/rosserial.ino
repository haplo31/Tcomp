#include <SimpleTimer.h>
#define _DEBUG true
SimpleTimer timer; // -> timer.setInterval

#include <ros.h>
//#include <std_msgs/Empty.h>
//#include <std_msgs/String.h>
//#include <std_msgs/Float64.h>
//#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int16.h>
//#include <std_msgs/MultiArrayDimension.h>
//#include <std_msgs/MultiArrayLayout.h>
//#include <std_msgs/Int64.h>
#include <geometry_msgs/Vector3.h>

// ros
ros::NodeHandle nh;
geometry_msgs::Vector3 floatmsg; // odometry is sent via this vector
std_msgs::Int16 intmsg; // end of movement
ros::Publisher chatter("chatter", &floatmsg);
ros::Publisher chatter2("chatter2", &intmsg);

//MAIN VARIABLES
float time = 0; // time at the beginning of the movement in deciseconds (ds), i.e. 10*time in seconds
int stop = 0; // stop = 1 between two movements, stop = 0 (which let enslavment run) during the movement 
int avancer = 0;
int reculer = 0;
int TournerGauche = 0;
int TournerDroite = 0;
float bilup,biluplup; // debug

//MOTOR
const int IN1= 13;  
const int IN3 = 12;
const int MotorG = 10; 
const int MotorD = 11;

//ULTRASOR
const int trig = 12; 
const int echo = 11; 
long lecture_echo;
long lecm;

//CODOR
long CodeurG = 0; // lowest level coder information
long CodeurD = 0;
long TotalCodeurG = 0; // sum of ticks
long TotalCodeurD = 0;
long prevTCG=0; // previous sum if ticks
long prevTCD=0;
int CodeurParalleleG = 0;
int CodeurParalleleD = 0;
const byte encoder0pinA = 21; //A pin -> the interrupt pin 2
const byte encoder0pinB = 4; //B pin -> the digital pin 4
const byte encoder1pinA = 20; //A pin -> the interrupt pin 2
const byte encoder1pinB = 14;//B pin -> the digital pin 4
byte encoder0PinALast;
byte encoder1PinALast;
boolean DirectionD; // rotation direction
boolean DirectionG; // rotation direction

//FRECATOR
const int frequence_echantillonnage = 50;  // enslavement execution frequency
const int rapport_reducteur = 51; // Rapport entre le nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 26; // Nombre de tick codeuse par tour de l'arbre moteur
 
//COMANDOR
float rotationdegres = 0; // rotation command
int distancecm = 0; // distance command
float botch; // for triangle command (when it has to decrease command)
float timef, timef2; // for trapez/triangle command in float
float CMG = 1; // nombre de tours de roue par seconde en croisiere
float CMD = 1;
float consigne_moteur_nombre_tours_par_secondeG = 0; //variable command (nbr tour/sec) for trapez/triangle
float consigne_moteur_nombre_tours_par_secondeD = 0;

//TCOMPOR DATA
const float diamrouecm = 12.1;
const float distancerouecm = 33; 

//ASSERVISSOR
int cmdG = 0; // (enslaved) commands actually feeding the motor
int cmdD = 0;
float erreur_precedenteG = 0;
float erreur_precedenteD = 0;
float somme_erreurG = 0; // Somme des erreurs pour l'int?grateur
float somme_erreurD = 0; // Somme des erreurs pour l'int?grateur
const float kp = 235; // Coefficient proportionnel
const float ki = 12; // Coefficient int?grateur
const float kd = 50; // Coefficient d?rivateur

//ASSERVISSOR PARALLELOR // UNUSED, variables remain 0
float cmdParallele = 0; // parallel correction command which directly modify 
//the high level command consigne_moteur_nombre_tours_par_secondeG
int erreurParallele = 0;
int erreur_precedenteParallele = 0;
int somme_erreurParallele = 0;   
float kpp = 0.02; // Coefficient proportionnel
float kii = 0.0; // Coefficient int?grateur
float kdd = 0.0; // Coefficient d?rivateur

// cmd message reception
// "chic le parseur de commande!" Albert Einstein
void messageCb(const std_msgs::Int16& cmd){ 
	if (cmd.data<1000 && stop==1)
	{
		distancecm=cmd.data;
		avancer=1;
      		time=0;
      		stop=0;
   	}
   	else if (cmd.data<2000 && stop==1)
   	{
      		distancecm=cmd.data-1000;
      		reculer=1;
      		time=0;
      		stop=0;
   	}
   	else if (cmd.data<3000 && stop==1)
   	{
      		rotationdegres=cmd.data-2000;
      		TournerGauche=1;
      		time=0;
      		stop=0;
   	}
   	else if (cmd.data<4000 && stop==1)
   	{
      		rotationdegres=cmd.data-3000;
      		TournerDroite=1;
      		time=0;
     		stop=0;   
   	}
   	else
   	{
      		distancecm=0;
      		rotationdegres=0;
      		stop=1;
      		analogWrite(MotorD, 0);
      		analogWrite(MotorG, 0);
   	}
   	//chatterBoy2();
}

ros::Subscriber<std_msgs::Int16> sub("toggle_led", &messageCb );

void setup() 
{
	//rosserial
	nh.initNode();
	nh.advertise(chatter);
	nh.advertise(chatter2);
	nh.subscribe(sub);
	
	EncoderInit(); //Initialize the module encoder (odometry)
	Serial.begin(57600);
//      Serial.begin(115700);   // Initialisation port COM
	pinMode(IN1,OUTPUT);
	//pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	//pinMode(IN4,OUTPUT);
	pinMode(MotorD,OUTPUT);
	pinMode(MotorG,OUTPUT);
	digitalWrite(IN1,HIGH);
	//digitalWrite(IN2,LOW);
	digitalWrite(IN3,LOW);
	//digitalWrite(IN4,HIGH);
	analogWrite(MotorD,0);  
	analogWrite(MotorG,0);  

 	timer.setInterval(1000/frequence_echantillonnage, asservissement); //interrupt pour PID et asservissement
	timer.setInterval(1000/frequence_echantillonnage, Avancer);
	//timer.setInterval(1000, Obstacle);
	timer.setInterval(100, tempo);
	// timer.setInterval(20,parallelisme);
	timer.setInterval(1000/frequence_echantillonnage, Tourner);
	// debut test rosserial        
	timer.setInterval(500,chatterBoy);
	//timer.setInterval(1000,chatterBoy2);
	// fin test rosserial
	pinMode(trig, OUTPUT); 
  	digitalWrite(trig, LOW); 
	pinMode(echo, INPUT); 
  	stop=1;
}

//time (ds)
void tempo()
{
	time++;
}

// odometry sender
void chatterBoy()
{
	floatmsg.x = ( ( (float) TotalCodeurG - (float) prevTCG)*diamrouecm*3.1415)/(2*rapport_reducteur*tick_par_tour_codeuse)/(100*0.5);
	floatmsg.y = ( ( (float) TotalCodeurD - (float) prevTCD)*diamrouecm*3.1415)/(2*rapport_reducteur*tick_par_tour_codeuse)/(100*0.5);
	floatmsg.z = avancer + 10*reculer + 100*TournerGauche + 1000*TournerDroite;
	prevTCG= TotalCodeurG;
	prevTCD= TotalCodeurD;
  	chatter.publish( &floatmsg );
	nh.spinOnce();
	if ((stop==1)) // TotalCodeurG/D not used for enslavement
	{
		if (prevTCG==TotalCodeurG)
		{
			prevTCG=0;
			TotalCodeurG=0;
		}
		if (prevTCD==TotalCodeurD)
		{
			prevTCD=0;
			TotalCodeurD=0;
		}
	}
}

// end of movement sender
void chatterBoy2()
{
/*
	if ((2>TournerGauche) && (TournerGauche>0.5))
	{*/
	intmsg.data = distancecm + rotationdegres; 
	chatter2.publish( &intmsg );
	nh.spinOnce();
/*
	}
	if ((2>TournerDroite) && (TournerDroite>0.5))
	{
		intmsg.data = 10; // distancecm + rotationdegres; 
		chatter2.publish( &intmsg );
		nh.spinOnce();
	}
	if ((2>TournerGauche) && (TournerGauche>0.5) && (2>TournerDroite) && (TournerDroite>0.5))
	{
		intmsg.data = 40; // distancecm + rotationdegres; 
		chatter2.publish( &intmsg );
		nh.spinOnce();
	}
*/
}

// ENCODORs
void EncoderInit() // used at setup
{
	DirectionD = false;
	DirectionG = true;
  	pinMode(encoder0pinB,INPUT);  
    	pinMode(encoder1pinB,INPUT); 
  	attachInterrupt(2, RwheelSpeed, CHANGE); 
    	attachInterrupt(3, LwheelSpeed, CHANGE);
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
  
void asservissement()
{
      
	if (stop==0)
    	{
 		// Reinitialisation du nombre de tick de la codeuse
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
		float erreurG = consigne_moteur_nombre_tours_par_secondeG - nb_tour_par_secG; // nombre de tours non faits par seconde
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

		// cmd motor bounds
		if(cmdG < 0) cmdG=0;
		if(cmdG > 255) cmdG = 255;
		if(cmdD < 0) cmdD=0;
		if(cmdD>255) cmdD = 255;
		analogWrite(MotorD, cmdD); // command actually feeding the motor
		analogWrite(MotorG, cmdG); 

		// DEBUG
		bilup=(TotalCodeurG)*diamrouecm*3.14/(2*rapport_reducteur*tick_par_tour_codeuse);
		biluplup= (TotalCodeurD)*diamrouecm*3.14/(2*rapport_reducteur*tick_par_tour_codeuse);
   	}
}

void parallelisme() // unused
{
	erreurParallele=CodeurParalleleD-CodeurParalleleG;
	CodeurParalleleG=0;
	CodeurParalleleD=0;

	// Calcul de l'erreur
	somme_erreurParallele += erreurParallele;
	float delta_erreurParallele = erreurParallele - erreur_precedenteParallele;
	erreur_precedenteParallele = erreurParallele;

	// PID : calcul de la commande
	cmdParallele = kpp*erreurParallele + kii*somme_erreurParallele + kdd*delta_erreurParallele;
}

void Avancer ()
{
	if ( (avancer==1)  || (reculer==1) )
	{  
  		// if movement done
		if (( ((TotalCodeurG+TotalCodeurD)*diamrouecm*3.14)/(4*rapport_reducteur*tick_par_tour_codeuse) >= distancecm ))
		{
			stop=1;
			digitalWrite(IN1,HIGH);
			//digitalWrite(IN2,LOW);
			digitalWrite(IN3,LOW);
			//digitalWrite(IN4,HIGH);
       			// cmdD=255;
	  
     			consigne_moteur_nombre_tours_par_secondeG=0;
      			consigne_moteur_nombre_tours_par_secondeD=0;
     			cmdG=0;
     			cmdD=0;
     			analogWrite(MotorD, cmdD);
     			analogWrite(MotorG, cmdG);
     			chatterBoy2();
     			distancecm=0;
			TotalCodeurG=0;
			TotalCodeurD=0;	
			prevTCG=0;
			prevTCD=0;
     			avancer=0;
     			reculer=0;
     			time=0;
      			// delay(2000); 
     			// Serial.println("done");
		}  
		else // movement
		{
  			if (avancer==1)
  			{
      				digitalWrite(IN1,HIGH);
				//digitalWrite(IN2,LOW);
				digitalWrite(IN3,LOW);
				//digitalWrite(IN4,HIGH);
  			}
  			else if (reculer==1)
  			{
     				digitalWrite(IN1,LOW);
	  			//digitalWrite(IN2,HIGH);
				digitalWrite(IN3,HIGH);
				//digitalWrite(IN4,LOW);
  			}

			// command signal = triangle
 	 		if((distancecm/(3.14*diamrouecm))<1)
  			{
  				botch=sqrt((distancecm)/(diamrouecm*3.14));
 				if (time<(botch*10))
 				{
 					timef = (float) time; 
 					consigne_moteur_nombre_tours_par_secondeG = 0.1*(timef+cmdParallele);
 					consigne_moteur_nombre_tours_par_secondeD = 0.1*(timef-cmdParallele);
 					//Serial.println("Accel");
 				}
 				else
				{
 					timef2= (float) time;
 					//Serial.println(consigne_moteur_nombre_tours_par_secondeG);
 					consigne_moteur_nombre_tours_par_secondeG= botch-( 0.1*((timef2-timef)+cmdParallele) );
 					consigne_moteur_nombre_tours_par_secondeD = botch-( 0.1*((timef2-timef)-cmdParallele) );
					// if real command too tiny: command = 0
  					if  ((consigne_moteur_nombre_tours_par_secondeG<0.05)||(consigne_moteur_nombre_tours_par_secondeD<0.05))
  					{
  						distancecm=0;
  					}
  				}	
  			}
 			else // command signal = trapez
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

void Tourner ()
{
	if ((TournerGauche==1)||(TournerDroite==1))
	{  
		// if movement done
		if ( (((TotalCodeurG+TotalCodeurD)*diamrouecm*3.14)/(4*rapport_reducteur*tick_par_tour_codeuse)) >= ((rotationdegres/360)*distancerouecm*3.14) )
		{
    			consigne_moteur_nombre_tours_par_secondeG=0;
      			consigne_moteur_nombre_tours_par_secondeD=0;
     			cmdG=0;
     			cmdD=0;
     			analogWrite(MotorD, cmdD);
     			analogWrite(MotorG, cmdG);
  			rotationdegres=0;
  			chatterBoy2(); 
			TotalCodeurG=0;
			TotalCodeurD=0;	
			prevTCG=0;
			prevTCD=0;
  			if (TournerGauche==1)
  			{
				digitalWrite(IN1,HIGH);
				//digitalWrite(IN2,LOW);
  			}
			else if (TournerDroite==1)
			{
				digitalWrite(IN3,LOW);
				//digitalWrite(IN4,HIGH);
			}
			stop=1;
			TournerGauche=0;
			TournerDroite=0;
			time=0;
		}
		else // movement
		{ 
			// rotation direction definition
			if (TournerGauche==1)
			{
				digitalWrite(IN1,LOW);
				//digitalWrite(IN2,HIGH); 
			}
			else if (TournerDroite==1)
			{
				digitalWrite(IN3,HIGH);
				//digitalWrite(IN4,LOW);
			}
			
			distancecm=(rotationdegres/360)*distancerouecm*3.14;
			// triangle
			if((distancecm/(3.14*diamrouecm))<1)
			{
				botch=sqrt((distancecm)/(diamrouecm*3.14));
				if (time<(botch*10) )	
				{
					timef = (float) time; 
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
			else // trapez
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
						rotationdegres=0;
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
	lecm = lecture_echo / 58; 
  	if (lecm<15)
 	{
    		stop=1;
   		CMG=0;
   		CMD=0;
       		cmdG=0;
     		cmdD=0;
     		analogWrite(MotorD, cmdD);
		analogWrite(MotorG, cmdG);
		stop=1;
     		//Serial.println ("Obstacle");
	}   
}  
  
/* Fonction principale */
void loop()
{
	timer.run();
	//nh.spinOnce(); 
   	//delay(1); 
}
