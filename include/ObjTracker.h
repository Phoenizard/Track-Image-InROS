#ifndef OBJECT_TRACKER_H
#define OBJECT_TRACKER_H

#include <ros/ros.h>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>
using namespace std;
using namespace cv;

// string trackerType[7] = {"BOOSTING","MIL","KCF","TLD","MEDIANFLOW","MOSSE","CSRT"};

class SubPuber
{
private:
    ros::NodeHandle nodeHandle;
    ros::Subscriber imgSub;
    ros::Publisher trackobj;
    cv::Rect2d detect(Mat rawImage);
    Ptr<Tracker> tracker;
    cv::Rect2d bbox;
    int state = 0;
public:
    // int flag = 2;
    // 0:detect     1:auto-track
    SubPuber()
    {
        imgSub = nodeHandle.subscribe("/camera/color/image_raw", 1, &SubPuber::ObjectTracker, this);
        trackobj = nodeHandle.advertise<sensor_msgs::Image>("/tracker", 1);
        tracker = TrackerKCF::create();
    }

    void ObjectTracker(const sensor_msgs::ImageConstPtr &frontRGBImg)
    {
        Mat image;
        try
        {
            image = cv_bridge::toCvShare(frontRGBImg, "bgr8")->image;
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert to image!");
            return;
        }

        if(state == 0){
            bbox = bbox = selectROI(image, false);
            tracker->init(image,bbox);
            state = 1;
        }
        else {
            bool ok = tracker->update(image,bbox);
            if(ok) {
                rectangle(image, bbox, Scalar(255,0,0), 4);
                cout << endl << bbox.tl() << endl << bbox.br() << endl;
            }else {
                cout << endl << "TrackLost" << endl;
                state = 0;
            }
        }

        // image = ProcessImg(image);
        //sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", image).toImageMsg();
        // use it when the image is grey
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        // use it when the image is RGB
        trackobj.publish(*msg);
    }
};
#endif //OBJECT_TRACKER_H
