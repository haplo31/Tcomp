#include <iostream>
#include <string>
#include <fstream>
#include "ros/ros.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "std_msgs/String.h"
//#include <sstream>
#include "utils/utils.h"
#include <nav_msgs/Path.h>
#include "std_msgs/String.h"
#include <ratslam_ros/TopologicalMap.h>

#include "ratslam/experience_map.h"
#include <ratslam_ros/TopologicalAction.h>
#include <nav_msgs/Odometry.h>
//#include "graphics/experience_map_scene.h"
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include <boost/property_tree/ini_parser.hpp>

#include <tf/transform_broadcaster.h>

#include <visualization_msgs/Marker.h>
#include <nav_msgs/Path.h>

#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Header.h>
#include <nav_msgs/MapMetaData.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
//ratslam_ros::TopologicalMap em_map;

#include <vector>

using namespace ratslam;
using namespace cv;
using namespace std;

cv::Mat I;
nav_msgs::OccupancyGrid publishedMAP;
ros::Publisher MAPpublisher;
int cpt;
std::vector<int8_t> occGrid;
int W = 100;
int H = 100;

void chatterCallback(ratslam_ros::TopologicalMapConstPtr em_map, ratslam::ExperienceMap *em2)
{
	cpt++;
	// viz data?
	//cerr << em_map->node[0].pose.position.x << endl;
        //cerr << em_map->node[0].pose.position.y << endl; 
	//float xxx = path->node[0].pose.position.x;
	//float yyy = path->node[0].pose.position.y;    
	//  float xxx = path.poses[0].position.x;
	//  float yyy = path.poses[0].position.y;

	int NB = em_map->node.size();
	double* tabloX = new double[NB];
	double* tabloY = new double[NB];

	cerr << "\n\n!!MAP!!\n" << endl;
	
	// load X and Y values
	for (int i = 0; i < NB; i++) 
	{
		tabloX[i] = em_map->node[i].pose.position.x*10;
		tabloY[i] = em_map->node[i].pose.position.y*10;
		cerr << "x: " << tabloX[i] << endl;
		cerr << "y: " << tabloY[i] << endl; 
	}

	double maximumX = tabloX[0];
	double maximumY = tabloY[0];
	double minimumX = tabloX[0];
	double minimumY = tabloY[0];

	// ajust max and min
	for (int i = 0; i < NB; i++)
	{
		//cerr << tabloX[i] << " " << tabloY;
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
		tabloX[i] = floor(tabloX[i]) + 20;
		tabloY[i] = floor(tabloY[i]) + 20;
	}

	for (int j=0;j<H*W;j++)
	{
			occGrid[j]=0;
	}

	for (int i=0;i<NB;i++)
	{
		for (int j=0;j<H*W;j++)
		{
			if (j==(tabloX[i]*W+tabloY[i]))
			{
				occGrid[j]=100;
			}
		}
	}
//	std::cerr << "bondouheu: X = ( " << minimumX << " , " << maximumX << " )     Y = ( " << minimumY << " , " << maximumY << " ) " << std::endl;   

	// ON TOUCHE A LIMAGE A PARTIR DICI: 
	// -> publier un nav_msgs/OccupancyGrid à la place
	// pour cela, écrire un nav_msgs/OccupancyGrid publisher
	// regarder les publications de vector3 dans rosserial.ino

/* IMAGE
	int WIDTH = 600, HEIGHT = 600;
	I = Mat::zeros(HEIGHT, WIDTH, CV_8UC1);
fin IMAGE*/
	
	//change pixel values
	// WARNING: if only one value, division by 0
	for (int i = 1; i < NB; i++)
	{
		//cerr << " " << tabloX[i] << " " << tabloY[i] << endl;
		double pointX = (tabloX[i] - minimumX)*I.rows/(maximumX-minimumX);
		double pointY = (tabloY[i] - minimumY)*I.cols/(maximumY-minimumY);
		int pixelX = floor(pointX);
		int pixelY = floor(pointY);
// IMAGE		I.at<uchar>(pixelX,pixelY) = 254; 
	}
/*IMAGE
	IplImage iplimg = I;
	imshow("la map", I);
	cvWaitKey(2); 
fin IMAGE */

	nav_msgs::MapMetaData metaData;
        metaData.resolution = 1;//0.05;
        metaData.width = W;
        metaData.height = H;
	publishedMAP.header.seq = cpt;
	publishedMAP.header.stamp = ros::Time::now();
	publishedMAP.header.frame_id = "map";
//	publishedMAP.info.resolution = 0.05;
	//publishedMAP.info.width = 20;
//	publishedMAP.info.height = 20;
//	publishedMAP.info.origin.position.x=0.0;
//	publishedMAP.info.origin.position.y=0.0;
//	publishedMAP.info.origin.position.z=0.0;
	//std::vector<int> occGrid(40000);

	
	publishedMAP.data = occGrid;
        publishedMAP.info = metaData;

// MAINTENANT IL FAUT TRANSFORMER UN ENSEMBLE DE POINTS 
// EN GRILLE DOCCUPATION 5cm2 unitaire ie une case fait 0.05metres
// ET POUR CHAQUE POINT, il faut calculer quelle case c'est en discrétisant (casex,casey) 
// calculer l'indice
// colum_casey*nb_rowrow + row_casex
	MAPpublisher.publish(publishedMAP);
	cerr << "visual map updated [map]" << endl;
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
	if (!ros::isInitialized())
	{
		ros::init(argc, argv, "TOTOlistenerMAP");
	}
	
	ros::NodeHandle node;
	ratslam::ExperienceMap * em2; /* = new ratslam::ExperienceMap(ratslam_settings);*/
	ros::Subscriber sub_MAP = node.subscribe<ratslam_ros::TopologicalMap>(topic_root + "/ExperienceMap/Map", 0, boost::bind(chatterCallback, _1, em2),ros::VoidConstPtr(), ros::TransportHints().tcpNoDelay());
	cpt = 0;
	MAPpublisher = node.advertise<nav_msgs::OccupancyGrid>("map_publish", 1000);
	occGrid.resize(H*W);
	for (int i=0;i<W*H;i++)
        {
		//cerr << ".";
                if (i%2==0)
                {
                        occGrid[i]=59;
                }
                else
                {
                        occGrid[i]=0;
                }
        }
	cerr << endl;

	
//	int occGrid[4] = {1,2,50,100};
	//occGrid = new int[40000];
/*
	for (unsigned jojo=0;jojo<1000;jojo++)
	{	
		occGrid[jojo]=100;
	}
*/
/*
	for (unsigned jojo=1000;jojo<40000;jojo++)
	{	
		occGrid[jojo]=0;
	}
*/
	ros::spin();

	return 0;
}
