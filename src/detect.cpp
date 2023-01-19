#include "ObjTracker.h"

cv::Rect2d SubPuber::detect(cv::Mat rawImage)
{
    QRCodeDetector qrDector = QRCodeDetector();
    vector<Point2d> bbox_point;
    qrDector.detect(rawImage, bbox_point);
    Rect2d bbox;
    if(!bbox_point.empty()) {
        bbox = minAreaRect(bbox_point).boundingRect();
        rectangle(rawImage, bbox, Scalar(0,0,255),8,8);
        ROS_INFO("Get it");
        // cout << bbox.area() << endl;
    }else {
        ROS_INFO("No target");
    }
    return bbox;
}