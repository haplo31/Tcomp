/*
 * openRatSLAM
 *
 * utils - General purpose utility helper functions mainly for angles and readings settings
 *
 * Copyright (C) 2012
 * David Ball (david.ball@qut.edu.au) (1), Scott Heath (scott.heath@uqconnect.edu.au) (2)
 *
 * RatSLAM algorithm by:
 * Michael Milford (1) and Gordon Wyeth (1) ([michael.milford, gordon.wyeth]@qut.edu.au)
 *
 * 1. Queensland University of Technology, Australia
 * 2. The University of Queensland, Australia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "utils/utils.h"

#include <boost/property_tree/ini_parser.hpp>

#include <ros/ros.h>

#include "ratslam/experience_map.h"
#include <ratslam_ros/TopologicalAction.h>
#include <nav_msgs/Odometry.h>
#include "graphics/experience_map_scene.h"
#include <ratslam_ros/TopologicalMap.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>
#include <tf/transform_broadcaster.h>

#include <visualization_msgs/Marker.h>
#include <nav_msgs/Path.h>

ros::Publisher pub_em;
ros::Publisher pub_pose;
ros::Publisher pub_em_markers;
ros::Publisher pub_goal_path;
geometry_msgs::PoseStamped pose_output;
ratslam_ros::TopologicalMap em_map;
visualization_msgs::Marker em_marker;

/*
ros::Publisher pub_lesExperiences;
nav_msgs::Path lesExperiences;
*/

//int compteurTOTO = 0;

cv::Mat I;

#ifdef HAVE_IRRLICHT
#include "graphics/experience_map_scene.h"
ratslam::ExperienceMapScene *ems;
bool use_graphics;
#endif

using namespace ratslam;
using namespace cv;
using namespace std;

void odo_callback(nav_msgs::OdometryConstPtr odo, ratslam::ExperienceMap *em)
{
  ROS_DEBUG_STREAM("EM:odo_callback{" << ros::Time::now() << "} seq=" << odo->header.seq << " v=" << odo->twist.twist.linear.x << " r=" << odo->twist.twist.angular.z);

  static ros::Time prev_time(0);

  if (prev_time.toSec() > 0)
  {
    double time_diff = (odo->header.stamp - prev_time).toSec();
    em->on_odo(odo->twist.twist.linear.x, odo->twist.twist.angular.z, time_diff);
  }

  static ros::Time prev_goal_update(0);

  if (em->get_current_goal_id() >= 0)
  {
    // (prev_goal_update.toSec() == 0 || (odo->header.stamp - prev_goal_update).toSec() > 5)
    //em->calculate_path_to_goal(odo->header.stamp.toSec());

    prev_goal_update = odo->header.stamp;

    em->calculate_path_to_goal(odo->header.stamp.toSec());

    static nav_msgs::Path path;
    if (em->get_current_goal_id() >= 0)
    {
      em->get_goal_waypoint();

      static geometry_msgs::PoseStamped pose;
      path.header.stamp = ros::Time::now();
      path.header.frame_id = "1";

      pose.header.seq = 0;
      pose.header.frame_id = "1";
      path.poses.clear();
      unsigned int trace_exp_id = em->get_goals()[0];
      while (trace_exp_id != em->get_goal_path_final_exp())
      {
        pose.pose.position.x = em->get_experience(trace_exp_id)->x_m;
        pose.pose.position.y = em->get_experience(trace_exp_id)->y_m;
        path.poses.push_back(pose);
        pose.header.seq++;

        trace_exp_id = em->get_experience(trace_exp_id)->goal_to_current;
      }

      pub_goal_path.publish(path);

      path.header.seq++;

    }
    else
    {
      path.header.stamp = ros::Time::now();
      path.header.frame_id = "1";
      path.poses.clear();
      pub_goal_path.publish(path);

      path.header.seq++;
    }
  }

  prev_time = odo->header.stamp;
}

void action_callback(ratslam_ros::TopologicalActionConstPtr action, ratslam::ExperienceMap *em)
{

	cerr << "EM EM EM on est dans action_callback EM EM EM" << endl;
	cerr << "EM EM EM on est dans action_callback EM EM EM" << endl;	
	cerr << "EM EM EM on est dans action_callback EM EM EM" << endl;
	cerr << "EM EM EM on est dans action_callback EM EM EM" << endl;
  ROS_DEBUG_STREAM("EM:action_callback{" << ros::Time::now() << "} action=" << action->action << " src=" << action->src_id << " dst=" << action->dest_id);

  switch (action->action)
  {
    case ratslam_ros::TopologicalAction::CREATE_NODE:
      em->on_create_experience(action->dest_id);
      em->on_set_experience(action->dest_id, 0);
      break;

    case ratslam_ros::TopologicalAction::CREATE_EDGE:
      em->on_create_link(action->src_id, action->dest_id, action->relative_rad);
      em->on_set_experience(action->dest_id, action->relative_rad);
      break;

    case ratslam_ros::TopologicalAction::SET_NODE:
      em->on_set_experience(action->dest_id, action->relative_rad);
      break;

  }

  em->iterate();

  pose_output.header.stamp = ros::Time::now();
  pose_output.header.seq++;
  pose_output.header.frame_id = "1";
  pose_output.pose.position.x = em->get_experience(em->get_current_id())->x_m;
  pose_output.pose.position.y = em->get_experience(em->get_current_id())->y_m;
  pose_output.pose.position.z = 0;
  pose_output.pose.orientation.x = 0;
  pose_output.pose.orientation.y = 0;
  pose_output.pose.orientation.z = sin(em->get_experience(em->get_current_id())->th_rad / 2.0);
  pose_output.pose.orientation.w = cos(em->get_experience(em->get_current_id())->th_rad / 2.0);
  pub_pose.publish(pose_output);

  static ros::Time prev_pub_time(0);

  if (action->header.stamp - prev_pub_time > ros::Duration(30.0)) // remettre à 30 si bug
  {
    cerr << "CA FAIT 30 SECS!!!!" << endl;
    prev_pub_time = action->header.stamp;

    em_map.header.stamp = ros::Time::now();
    em_map.header.seq++;
    em_map.node_count = em->get_num_experiences();
    em_map.node.resize(em->get_num_experiences());
    for (int i = 0; i < em->get_num_experiences(); i++)
    {
      em_map.node[i].id = em->get_experience(i)->id;
      em_map.node[i].pose.position.x = em->get_experience(i)->x_m;
      em_map.node[i].pose.position.y = em->get_experience(i)->y_m;    

      em_map.node[i].pose.orientation.x = 0;
      em_map.node[i].pose.orientation.y = 0;
      em_map.node[i].pose.orientation.z = sin(em->get_experience(i)->th_rad / 2.0);
      em_map.node[i].pose.orientation.w = cos(em->get_experience(i)->th_rad / 2.0);
    /*
	cerr << em->get_experience(i)->id << endl;

	cerr << em->get_experience(i)->x_m << endl;
	cerr << em->get_experience(i)->y_m << endl;
	
	cerr << sin(em->get_experience(i)->th_rad / 2.0) << endl;
	cerr << cos(em->get_experience(i)->th_rad / 2.0) << endl;
*/
    }

    em_map.edge_count = em->get_num_links();
    em_map.edge.resize(em->get_num_links());
    for (int i = 0; i < em->get_num_links(); i++) // TODO TODO TODO CA !!!!!
    {
      em_map.edge[i].source_id = em->get_link(i)->exp_from_id;
      em_map.edge[i].destination_id = em->get_link(i)->exp_to_id;
      em_map.edge[i].duration = ros::Duration(em->get_link(i)->delta_time_s);
      em_map.edge[i].transform.translation.x = em->get_link(i)->d * cos(em->get_link(i)->heading_rad);
      em_map.edge[i].transform.translation.y = em->get_link(i)->d * sin(em->get_link(i)->heading_rad);
      em_map.edge[i].transform.rotation.x = 0;
      em_map.edge[i].transform.rotation.y = 0;
      em_map.edge[i].transform.rotation.z = sin(em->get_link(i)->facing_rad / 2.0);
      em_map.edge[i].transform.rotation.w = cos(em->get_link(i)->facing_rad / 2.0); 
    }
    pub_em.publish(em_map); // c'est la qu'on BALANCE LA MAP MANGE SES MORTS!!!
  }

  em_marker.header.stamp = ros::Time::now();
  em_marker.header.seq++;
  em_marker.header.frame_id = "1";
  em_marker.type = visualization_msgs::Marker::LINE_LIST;
  em_marker.points.resize(em->get_num_links() * 2);
  em_marker.action = visualization_msgs::Marker::ADD;
  em_marker.scale.x = 0.01;
  //em_marker.scale.y = 1;
  //em_marker.scale.z = 1;
  em_marker.color.a = 1;
  em_marker.ns = "em";
  em_marker.id = 0;
  em_marker.pose.orientation.x = 0;
  em_marker.pose.orientation.y = 0;
  em_marker.pose.orientation.z = 0;
  em_marker.pose.orientation.w = 1;
  for (int i = 0; i < em->get_num_links(); i++)

  {
    em_marker.points[i * 2].x = em->get_experience(em->get_link(i)->exp_from_id)->x_m;
    em_marker.points[i * 2].y = em->get_experience(em->get_link(i)->exp_from_id)->y_m;
    em_marker.points[i * 2].z = 0;
    em_marker.points[i * 2 + 1].x = em->get_experience(em->get_link(i)->exp_to_id)->x_m;
    em_marker.points[i * 2 + 1].y = em->get_experience(em->get_link(i)->exp_to_id)->y_m;
    em_marker.points[i * 2 + 1].z = 0;
  }

  pub_em_markers.publish(em_marker);


#ifdef HAVE_IRRLICHT
  if (use_graphics)
  {
    ems->update_scene();
    ems->draw_all();
  }
#endif



int NB = em->get_num_experiences(); 
double* tabloX = new double[NB];
double* tabloY = new double[NB];
for (int i = 0; i < NB; i++) // PUBLISH TOUT CA DANS UN NOEUD (ODOM?)
{
	tabloX[i] = em->get_experience(i)->x_m;
	tabloY[i] = em->get_experience(i)->y_m;
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

//cerr << " " << tabloX[i] << " " << tabloY[i] << endl;

/*
double pointX = (tabloX[i] - minimumX)*I.rows/(maximumX-minimumX);
double pointY = (tabloY[i] - minimumY)*I.cols/(maximumY-minimumY);
int pixelX = floor(pointX);
int pixelY = floor(pointY);

//cerr << "le point: " << em->get_experience(i)->x_m << " -- " << em->get_experience(i)->y_m << "\n\n" << endl;
	I.at<uchar>(pixelX,pixelY) = 254; 
*/
}
/*
IplImage iplimg = I;
cvShowImage("Original", &iplimg);
//imshow("la map", I);
cvWaitKey(2); 
*/

cerr << "EM EM EM fin action_callback EM EM EM" << endl;
	cerr << "EM EM EM fin action_callback EM EM EM" << endl;	
	cerr << "EM EM EM fin action_callback EM EM EM" << endl;
	cerr << "EM EM EM fin action_callback EM EM EM" << endl;

}

void set_goal_pose_callback(geometry_msgs::PoseStampedConstPtr pose, ratslam::ExperienceMap * em)
{
  em->add_goal(pose->pose.position.x, pose->pose.position.y);

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char * argv[])
{

  //compteurTOTO = 0;

  ROS_INFO_STREAM(argv[0] << " - openRatSLAM Copyright (C) 2012 David Ball and Scott Heath");
  ROS_INFO_STREAM("RatSLAM algorithm by Michael Milford and Gordon Wyeth");
  ROS_INFO_STREAM("Distributed under the GNU GPL v3, see the included license file.");
  std::cerr << " IMAGE!!!!! EM " << std::endl;
  std::cerr << " IMAGE!!!!! EM " << std::endl;
  std::cerr << " IMAGE!!!!! EM " << std::endl;
  std::cerr << " IMAGE!!!!! EM " << std::endl;
  std::cerr << " IMAGE!!!!! EM " << std::endl;    
  //int WIDTH = 512, HEIGHT = 512;
   //Mat I = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
   //imshow("la map", I);
   //cvWaitKey(2);      
   //maintenant afficher dans cette image le dessin de l'experience map

  if (argc < 2)
  {
    ROS_FATAL_STREAM("USAGE: " << argv[0] << " <config_file>");
    exit(-1);
  }
  std::string topic_root = "";
  boost::property_tree::ptree settings, general_settings, ratslam_settings;
  read_ini(argv[1], settings);

  get_setting_child(ratslam_settings, settings, "ratslam", true);
  get_setting_child(general_settings, settings, "general", true);
  get_setting_from_ptree(topic_root, general_settings, "topic_root", (std::string)"");

  if (!ros::isInitialized())  // si pas init, on init
  {
    ros::init(argc, argv, "RatSLAMExperienceMap");
  }
  ros::NodeHandle node; // declaration du noeud



  ratslam::ExperienceMap * em = new ratslam::ExperienceMap(ratslam_settings);




// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  pub_em = node.advertise<ratslam_ros::TopologicalMap>(topic_root + "/ExperienceMap/Map", 1);

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




  pub_em_markers = node.advertise<visualization_msgs::Marker>(topic_root + "/ExperienceMap/MapMarker", 1); // TODO TODO TODO ca c'est l'avenir

  pub_pose = node.advertise<geometry_msgs::PoseStamped>(topic_root + "/ExperienceMap/RobotPose", 1);

  pub_goal_path = node.advertise<nav_msgs::Path>(topic_root + "/ExperienceMap/PathToGoal", 1);

  ros::Subscriber sub_odometry = node.subscribe<nav_msgs::Odometry>(topic_root + "/odom", 0, boost::bind(odo_callback, _1, em), ros::VoidConstPtr(),
                                                                    ros::TransportHints().tcpNoDelay());
  ros::Subscriber sub_action = node.subscribe<ratslam_ros::TopologicalAction>(topic_root + "/PoseCell/TopologicalAction", 0, boost::bind(action_callback, _1, em),
                                                                              ros::VoidConstPtr(), ros::TransportHints().tcpNoDelay());



  ros::Subscriber sub_goal = node.subscribe<geometry_msgs::PoseStamped>(topic_root + "/ExperienceMap/SetGoalPose", 0, boost::bind(set_goal_pose_callback, _1, em),
                                                                        ros::VoidConstPtr(), ros::TransportHints().tcpNoDelay());

  //pub_lesExperiences = node.advertise<nav_msgs::Path>(topic_root + "/map", 1);

std::cerr << " EM avant irrlicht " << std::endl;

#ifdef HAVE_IRRLICHT
  boost::property_tree::ptree draw_settings;
  get_setting_child(draw_settings, settings, "draw", true);
  get_setting_from_ptree(use_graphics, draw_settings, "enable", true);
  if (use_graphics)
  {
    ems = new ratslam::ExperienceMapScene(draw_settings, em);
  }
#endif

  ros::spin();

  return 0;
}

