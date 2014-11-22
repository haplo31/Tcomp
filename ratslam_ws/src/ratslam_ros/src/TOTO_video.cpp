#include <iostream>
#include <string>
#include <fstream>
#include "ros/ros.h"
//#include "std_msgs/String.h"
//#include <sstream>
//#include <nav_msgs/Odometry.h>
#include "std_msgs/String.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"

#include <stdio.h>

#include <time.h> 

#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>

//#include <cv_bridge/CvBridge.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

using namespace std;

int main(int argc, char **argv)
{

	cerr << "EHOHHHHHH!!!!" << endl;
	
	ros::init(argc, argv, "TOTOtalkerVIDEO");
	ros::NodeHandle node;
//        string topic_root = "irat_red";
        string topic_root = "/newcollege/";

	image_transport::ImageTransport it(node);
	image_transport::Publisher pub_image = it.advertise(topic_root + "/camera/image", 0);

	ros::Rate loop_rate(10);
//ros::Rate loop_rate(40);	
	/* Variables */
	IplImage *im;
	CvCapture *avi;
	/* ouverture de la video */
	//avi = cvCaptureFromAVI("/home/drougard/catkin_ws/video_ratslam.avi");
	avi = cvCaptureFromAVI("/home/drougard/catkin_ws/oxford_newcollege/video_ratslam_newCollege.avi");
//	cv_bridge::cv_bridge bridge;

//	cerr << "EHOHHHHHH 2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222:  ---->>>>" << cvGrabFrame(avi) << endl;



	while (ros::ok())
  	{
		cvGrabFrame(avi);
		//if( cvGrabFrame(avi) )
		//{	
		 	im = cvRetrieveFrame(avi);
			cvShowImage("MONIMAGEDEFOUUUUUUU", im);
			cvWaitKey(2); 
		//}

// PROBLEME POUR PUBLISH

//bridge.fromIpltoRosImage(disparity, disparity_msg, "passthrough");
 //   pub.publish(disparity_msg);

		cv_bridge::CvImage cv_image;
		cv::Mat matIm = cv::Mat(im);
		cv_image.image = matIm;
		cv_image.encoding = "bgr8";


//		cv::Mat matIm = cv::cvarrToMat(im);
//		cv_bridge::CvImageConstPtr cv_ptr(new cv_bridge::CvImageConstPtr);
//		cv_ptr->image = matIm;

		sensor_msgs::ImageConstPtr pointeurSurImage; // = cv_ptr->toImageMsg();

//		im->toImageMsg(pointeurSurImage);
		
		// = im; // bridge.cvToImgMsg(&im, "passthrough"); // cv_bridge::toCvShare(im, BGR8);
		pointeurSurImage = cv_image.toImageMsg();
    		pub_image.publish(pointeurSurImage);

		ros::spinOnce();

	        loop_rate.sleep();
         }


   return 0;
}
