#include <iostream>
#include <string>
#include <fstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <nav_msgs/Odometry.h>
#include "std_msgs/String.h"
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int64.h>
#include <geometry_msgs/Vector3.h>

ros::Publisher pub_odometry;
ros::Publisher toggle_led;

int * commandes;
int numCommande;
int currentCommande;
int nbCommandes;
float prevDirection = 0;

using namespace std;

double string_to_double( const std::string& s )
 {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
 }  

uint32_t string_to_uint32( const std::string& s )
 {
   std::istringstream i(s);
   uint32_t x;
   if (!(i >> x))
     return 0;
   return x;
 }  


void chatterCallback(geometry_msgs::Vector3 floatmsg)
{
	// debut TODAY
	nav_msgs::Odometry odom;
    		//std_msgs::String msg;
		
	ros::Time hdst = ros::Time::now();
	odom.header.stamp = hdst;
   		
	//uint32_t hdseq = string_to_uint32(header2);// (uint32_t) header2;
	//uint32_t hdseq = 1;	
	odom.header.seq = 42;

	//set the position
	//odom.pose.pose.position.x = x;
    	//odom.pose.pose.position.y = y;
    	//odom.pose.pose.position.z = 0.0;
    	//odom.pose.pose.orientation = odom_quat;

    	   //set the velocity
    	//odom.child_frame_id = "base_link";
		
	float fx = 0;
	float fy = 0;
	if ((0.9 < floatmsg.z) && (floatmsg.z <1.1))
	{
		cerr << "main -- odom recept: AVANCE" << endl;
		fx = floatmsg.x;
		fy = floatmsg.y;
		prevDirection = floatmsg.z;
	}
	else if ((9.9 < floatmsg.z) && (floatmsg.z < 10.1)) 
	{
		cerr << "main -- odom recept: RECULE" << endl;
		fx = -floatmsg.x;
		fy = -floatmsg.y;
		prevDirection = floatmsg.z;
	}
	else if ((99.9 < floatmsg.z) && ( floatmsg.z < 100.1))
	{
		cerr << "main -- odom recept: TOURNE GAUCHE" << endl;
		fx = -floatmsg.x;
		fy = floatmsg.y;
		prevDirection = floatmsg.z;
	}
	else if ( (999.9 < floatmsg.z) && (floatmsg.z < 1000.1))
	{
		cerr << "main -- odom recept: TOURNE DROITE" << endl;
		fx = floatmsg.x;
		fy = -floatmsg.y;
		prevDirection = floatmsg.z;
	}
	else if ((-0.1 < floatmsg.z) && (floatmsg.z < 0.1))
	{
		cerr << "main -- odom ARRET -- concerv prevDirection ";
		if ((0.9 < prevDirection) && (prevDirection <1.1))
		{
			cerr << " AVANCE" << endl;
			fx = floatmsg.x;
			fy = floatmsg.y;
		}
		else if ((9.9 < prevDirection) && (prevDirection < 10.1)) 
		{
			cerr << " RECULE" << endl;
			fx = -floatmsg.x;
			fy = -floatmsg.y;
			prevDirection = floatmsg.z;
		}
		else if ((99.9 < prevDirection) && ( prevDirection < 100.1))
		{
			cerr << " TOURNE GAUCHE" << endl;
			fx = -floatmsg.x;
			fy = floatmsg.y;
			prevDirection = floatmsg.z;
		}
		else if ( (999.9 < prevDirection) && (prevDirection < 1000.1))
		{
			cerr << " TOURNE DROITE" << endl;
			fx = floatmsg.x;
			fy = -floatmsg.y;
			prevDirection = floatmsg.z;
		}
		else if ((-0.1 < prevDirection) && (prevDirection < 0.1))
		{
			cerr << " no movement received yet" << endl;
		}	
		else
		{
			cerr << " WARNING!! BUG IN DIRECTION SENDER!!! " << endl;
		}
	}
	else
	{
		cerr << " WARNING!! BUG IN DIRECTION SENDER!!! " << endl;
	}
	
	double leX = ((double) fx + (double) fy)/2;// string_to_double(linearX);
	//double leX = 0.1;
	odom.twist.twist.linear.x = leX;
	//odom.twist.twist.linear.y = vy;
	//double lA = 0.1;    		
	double lA = ((double) fx - (double) fy)/0.121; //string_to_double(angularZ); //(double) angularZ;
			
	odom.twist.twist.angular.z = lA;

	pub_odometry.publish(odom);

	cerr << "MAINTOTO!!: recup odom: "  << leX << " " << lA << " | " << floatmsg.x << " " << floatmsg.y << " " << floatmsg.z << endl;

//		ros::spinOnce();

//	        loop_rate.sleep();
//		cerr << "COUNT: " << count << endl;
//                ++count;

// end TODAY

}


void chatterCallback2(std_msgs::Int16 intmsg) //new 10/09/14
{
/*
	if ( (intmsg.data>5) && (intmsg.data<20))
	{
    cerr << "MAINTOTO2!!: *** test: ça tourne à droite!! " << intmsg << endl;
	}
	else if ((intmsg.data<5))
	{
    cerr << "MAINTOTO2!!: *** test: ça tourne à gauche!! " << intmsg << endl;
	}
	else 
	{
	cerr << "PAS COOL!!!!!"<< endl;
	}
*/
    double begin = ros::Time::now().toSec();
    double now = ros::Time::now().toSec();
/* 
   while (now-begin<1)
    {
	now = ros::Time::now().toSec();
    }
    std_msgs::Int16 bla1;
    bla1.data = 4100;
    toggle_led.publish(bla1);
*/	
/* TEST TOUURNAGAUCHE */

// TEST TOUURNAGAUCHE
    //begin = ros::Time::now().toSec();
    //now = ros::Time::now().toSec();
    while (now-begin<0.5)
    {
	now = ros::Time::now().toSec();
    }

    int lecture = commandes[currentCommande];
    cerr << "MAINTOTO: reçoit le int16 de fin, envoie la commande: " << lecture;
    std_msgs::Int16 bla;
    bla.data = lecture;
    //toggle_led.publish(bla);  
    cerr << " -- en fait, non " << endl;
    if (currentCommande==numCommande)
    {
	currentCommande=0;
    }
    else
    {
	currentCommande++;
    }

}


int main(int argc, char **argv)
{
		

	ifstream fichier("/home/odroid/commandes.txt", ios::in);  // on ouvre en lecture
/* 
	ifstream fichier("/home/drougard/catkin_ws/src/ratslam_ros/src/_slash_newcollege_slash_odom.csv", ios::in);
*/
	cout.flush();
	        

	// FAIRE UN TABLEAU DE INT QUI VA STOCKER LES COMMANDES
	string contenu = "";  // déclaration d'une chaîne qui contiendra la ligne lue
        getline(fichier, contenu);  // on met dans "contenu" la ligne
        cout << contenu << endl;  // on affiche la ligne
	commandes = new int[100];
	numCommande = 0;
	if(fichier)  // si l'ouverture a fonctionné
        {
		string commande = "            ";
		int cpt = 0;
		cerr << "COMMANDES:" << endl;
		for (unsigned i=0; i < contenu.size(); i++)
		{
			if(contenu[i]!=',')
			{
				commande[cpt] = contenu[i];
				cpt++;			
			}
			else
			{
				int numb;
				istringstream ( commande ) >> numb;
				commandes[numCommande] = numb;	
				cerr << commandes[numCommande] << " ";
				numCommande++;
				cpt=0;
				commande = "            ";
			}
		}      
		int numb;
		istringstream ( commande ) >> numb;
		commandes[numCommande] = numb;
		cerr << commandes[numCommande] << endl;
	}
        else
	{
		cerr << "CA CRAINT DU BOUDIN DANS MAINTOTO!!!" << endl;
	}	
	currentCommande=0;
	//ros::init(argc, argv, "listener");
	ros::init(argc, argv, "TOTOtalker");
	//ros::init(argc, argv, "actionSeq");
	ros::NodeHandle node;
        string topic_root = "irat_red";
     // string topic_root = "/newcollege/";

	pub_odometry = node.advertise<nav_msgs::Odometry>(topic_root + "/odom", 0);
	toggle_led = node.advertise<std_msgs::Int16>("toggle_led", 0);
	
	//ros::Duration(9).sleep();

	/* ros::Rate loop_rate(10);, TODAY
	int count = 0;
	int ligne=0;	
	int k=0;
*/

	ros::Subscriber sub = node.subscribe("chatter", 500, chatterCallback);	
	ros::Subscriber sub2 = node.subscribe("chatter2", 1000, chatterCallback2); //new 10/09/14
/*
	while (ros::ok())
  	{

		
		string header1 = "                     ";
		string header2 = "                     ";
		string linearX = "                     ";
		string angularZ = "                    ";
*/
/*
		 if( !fichier.eof() )
		 {	
			//getline(fichier, contenu);  // on met dans "contenu" la ligne
			k=0;
			int j=0;		
			getline(fichier, contenu);  // on met dans "contenu" la ligne
		
			int preums = 4;
			int deux = 5;
			int triss = 58;
			int quatro = 64;
			for (unsigned i=0; i < contenu.size(); i++)
			{			
				if(contenu[i]!=',')
				{
					//tablo[ligne][k][j] = contenu[i];
					if (k==preums)
					header1[j]  = contenu[i];
					if (k==deux)
					header2[j] = contenu[i];
					if (k==triss)
					linearX[j] = contenu[i];
					if (k==quatro)	
					angularZ[j] = contenu[i];
					j++;			
				}
				else
				{
					j=0;
					k++;
				}					
			}				
		}
		

		ligne++;*/

		//cerr << "TOTOpublish!!!!                 " << header1 << "      " << header2 << "          " <<  linearX << "         " << angularZ << endl;		


		
		
	/*	nav_msgs::Odometry odom; TODAY
    		//std_msgs::String msg;
		
		ros::Time hdst = ros::Time::now();
		odom.header.stamp = hdst;
   		
		uint32_t hdseq = string_to_uint32(header2);// (uint32_t) header2;
		//uint32_t hdseq = 1;	
		odom.header.seq = hdseq;

		//set the position
		//odom.pose.pose.position.x = x;
    		//odom.pose.pose.position.y = y;
    		//odom.pose.pose.position.z = 0.0;
    		//odom.pose.pose.orientation = odom_quat;

    		   //set the velocity
    		//odom.child_frame_id = "base_link";
		
		double leX = string_to_double(linearX);
		//double leX = 0.1;
    		odom.twist.twist.linear.x = leX;
    		//odom.twist.twist.linear.y = vy;
		//double lA = 0.1;    		
		double lA = string_to_double(angularZ); //(double) angularZ;		
		odom.twist.twist.angular.z = lA;

    		pub_odometry.publish(odom);

		ros::spinOnce();

	        loop_rate.sleep();
		cerr << "COUNT: " << count << endl;
                ++count;
*/


        /* } TODAY
*/
	

	ros::spin();
   return 0;
}
