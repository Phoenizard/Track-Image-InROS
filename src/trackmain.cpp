#include "ObjTracker.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tracker");
    ROS_INFO("Build Successfully");
    SubPuber tracker;
    // change the name
    ros::spin();
    return 0;
}