#include <iostream>
#include <string>
#include <fstream>
#include "ros/ros.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

//#include "std_msgs/String.h"
//#include <sstream>
#include "utils/utils.h"
#include <nav_msgs/Path.h>
#include "std_msgs/String.h"
#include <ratslam_ros/TopologicalMap.h>

#include "ratslam/experience_map.h"
#include <ratslam_ros/TopologicalAction.h>
#include <nav_msgs/Odometry.h>
#include "graphics/experience_map_scene.h"
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include <boost/property_tree/ini_parser.hpp>


#include <tf/transform_broadcaster.h>

#include <visualization_msgs/Marker.h>
#include <nav_msgs/Path.h>


//ratslam_ros::TopologicalMap em_map;

using namespace ratslam;
using namespace cv;
using namespace std;

cv::Mat I;

void chatterCallback(ratslam_ros::TopologicalMapConstPtr em_map, ratslam::ExperienceMap *em2)
{
	//cerr << em_map->node[0].pose.position.x << endl;
        //cerr << em_map->node[0].pose.position.y << endl; 
	//float xxx = path->node[0].pose.position.x;
	//float yyy = path->node[0].pose.position.y;    
	//  float xxx = path.poses[0].position.x;
	//  float yyy = path.poses[0].position.y;
  	cerr << " BONJOUR MESDAMES ET MESSIEURS!!!   LE POINT X:" << em_map->node[0].pose.position.x << " --- ET LE POINT Y:" << em_map->node[0].pose.position.y << endl;

int NB = em_map->node.size();
double* tabloX = new double[NB];
double* tabloY = new double[NB];
for (int i = 0; i < NB; i++) // PUBLISH TOUT CA DANS UN NOEUD (ODOM?)
{
	tabloX[i] = em_map->node[i].pose.position.x;
	tabloY[i] = em_map->node[i].pose.position.y;
	//lesExperiences.poses[i].pose.position.x = em->get_experience(i)->x_m;
	//lesExperiences.poses[i].pose.position.y = em->get_experience(i)->y_m;
}

/*
cerr << "AVANTTTTTTT !!!"  << endl;
//pub_lesExperiences.publish(lesExperiences);
cerr << "APREEESSSSSSSSSSSSSSSS !!!"  << endl;
*/
double maximumX = tabloX[0];
double maximumY = tabloY[0];
double minimumX = tabloX[0];
double minimumY = tabloY[0];

for (int i = 0; i < NB; i++)
{
	if (maximumX<tabloX[i]){
		maximumX = tabloX[i];
	}
	if (maximumY<tabloY[i]){
		maximumY = tabloY[i];
	}
	if (minimumX>tabloX[i]){
		minimumX = tabloX[i];
	}
	if (minimumY>tabloY[i]){
		minimumY = tabloY[i];
	}
//	cerr << "MIN X" << endl;
//	cerr << minimumX << endl;    
//	cerr << "MAX X" << endl;	
//	cerr << maximumX << endl;
//	cerr << "MIN Y" << endl;     
//	cerr << minimumY << endl;
//	cerr << "MAX Y" << endl;	
//	cerr << maximumY << endl; 


}

//compteurTOTO=compteurTOTO+20;
//compteurTOTO = compteurTOTO%255;

//cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
int WIDTH = 600, HEIGHT = 600;
I = Mat::zeros(HEIGHT, WIDTH, CV_8UC1);
//change some pixel value

// si il y a une seule valeur, on div par 0
for (int i = 1; i < NB; i++)
{

cerr << " " << tabloX[i] << " " << tabloY[i] << endl;


double pointX = (tabloX[i] - minimumX)*I.rows/(maximumX-minimumX);
double pointY = (tabloY[i] - minimumY)*I.cols/(maximumY-minimumY);
int pixelX = floor(pointX);
int pixelY = floor(pointY);

//cerr << "le point: " << em->get_experience(i)->x_m << " -- " << em->get_experience(i)->y_m << "\n\n" << endl;
	I.at<uchar>(pixelX,pixelY) = 254; 

}

IplImage iplimg = I;
cvShowImage("Original", &iplimg);
//imshow("la map", I);
cvWaitKey(2); 

cerr << "FIN BONJOUR MESDAMES ET MESSIEURS!!!" << endl;



}

int main(int argc, char * argv[])
{

  if (argc < 2)
  {
    ROS_FATAL_STREAM("USAGE: " << argv[0] << " <config_file>");
    exit(-1);
  }
  std::string topic_root = "";
  boost::property_tree::ptree settings, ratslam_settings, general_settings;
  read_ini(argv[1], settings);

  get_setting_child(ratslam_settings, settings, "ratslam", true);
  get_setting_child(general_settings, settings, "general", true);
  get_setting_from_ptree(topic_root, general_settings, "topic_root", (std::string) "");

	cerr << "-1-" << endl;

//  std::string topic_root = "/irat_red/";

	cerr << "-1-" << endl;

if (!ros::isInitialized())
  {
    ros::init(argc, argv, "TOTOlistenerMAP");
  }

	cerr << "-2-   " + topic_root << endl;

  ros::NodeHandle node;

	cerr << "-3-" << endl;  

  ratslam::ExperienceMap * em2; /* = new ratslam::ExperienceMap(ratslam_settings);*/

		cerr << "-3-" << endl;	
	  
	ros::Subscriber sub_MAP = node.subscribe<ratslam_ros::TopologicalMap>(topic_root + "/ExperienceMap/Map", 0, boost::bind(chatterCallback, _1, em2),
                                                                              ros::VoidConstPtr(), ros::TransportHints().tcpNoDelay());

	cerr << "-4-" << endl;	

  ros::spin();

	cerr << "-5-" << endl;

  return 0;
}
