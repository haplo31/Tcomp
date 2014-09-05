#include <iostream>
#include <string>
#include <fstream>
#include "ros/ros.h"
//#include "std_msgs/String.h"
//#include <sstream>
#include <nav_msgs/Odometry.h>
#include "std_msgs/String.h"
#include <std_msgs/Float64.h>

ros::Publisher pub_odometry;
 
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


void chatterCallback(std_msgs::Float64 floatmsg)
{
  cerr << "MAINTOTO!!: " << floatmsg << endl;

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
		
		double leX = (double) floatmsg.data;// string_to_double(linearX);
		//double leX = 0.1;
    		odom.twist.twist.linear.x = leX;
    		//odom.twist.twist.linear.y = vy;
		//double lA = 0.1;    		
		double lA = (double) floatmsg.data; //string_to_double(angularZ); //(double) angularZ;		
		odom.twist.twist.angular.z = lA;

    		pub_odometry.publish(odom);

//		ros::spinOnce();

//	        loop_rate.sleep();
//		cerr << "COUNT: " << count << endl;
//                ++count;

// end TODAY

}

int main(int argc, char **argv)
{
		

	//ifstream fichier("/home/drougard/catkin_ws/src/ratslam_ros/src/_slash_irat_red_slash_odom.csv", ios::in);  // on ouvre en lecture
/* TODAY	
	ifstream fichier("/home/drougard/catkin_ws/src/ratslam_ros/src/_slash_newcollege_slash_odom.csv", ios::in);
	cout.flush();
        string contenu = "";  // déclaration d'une chaîne qui contiendra la ligne lue
        getline(fichier, contenu);  // on met dans "contenu" la ligne
        cout << contenu << endl;  // on affiche la ligne
        
	if(fichier)  // si l'ouverture a fonctionné
        {

        }
        else
	{
		cerr << "CA CRAINT DU BOUDIN DANS MAINTOTO!!!" << endl;
	}	
*/
	ros::init(argc, argv, "listener");
	ros::init(argc, argv, "TOTOtalker");
	ros::NodeHandle node;
        string topic_root = "irat_red";
     // string topic_root = "/newcollege/";

	pub_odometry = node.advertise<nav_msgs::Odometry>(topic_root + "/odom", 0);

	//ros::Duration(9).sleep();

	/* ros::Rate loop_rate(10);, TODAY
	int count = 0;
	int ligne=0;	
	int k=0;
*/

	ros::Subscriber sub = node.subscribe("chatter", 1000, chatterCallback);	
/* TODAY
	while (ros::ok())
  	{

		
		string header1 = "                     ";
		string header2 = "                     ";
		string linearX = "                     ";
		string angularZ = "                    ";
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
		

		ligne++;

		//cerr << "TOTOpublish!!!!                 " << header1 << "      " << header2 << "          " <<  linearX << "         " << angularZ << endl;		

*/
		
		
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
	 fichier.close();
*/
	ros::spin();
   return 0;
}
