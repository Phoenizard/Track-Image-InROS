## TrackImage in ROS

### 项目描述

本项目是对追踪算法的实际运用，使用的是TrackerKCF
提供了ROI接口，手动框选目标并实现追踪

### 使用方法
此项目为ROS软件包形式，如需使用，请复制到工作空间下的
src文件夹中，运行以下代码完成编译，并且添加环境变量：

```commandline
cd ~/{workspace_name}
catkin_make
```


使用时需要配合realsense的ROS包：
```commandline
roslaunch realsense2_camera rs_camera.launch
rosrun object-camera-transform solvepnp2d3d
rviz
```

追踪轮廓将在rviz中出现