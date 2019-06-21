#pragma once

#include "ros/ros.h"
#include "std_srvs/Trigger.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <stdlib.h>
#include <tf/transform_datatypes.h>




using namespace std;

struct Angles {
    double roll;
    double pitch;
    double yaw;
};


bool getPosition(std_srvs::Trigger::Request &xbox_button_request,
    std_srvs::Trigger::Response &position_response);

void getPositionInputandWriteToFile(const geometry_msgs::PoseStamped &pos );
Angles convertQuternionToRollPitchYaw(const geometry_msgs::PoseStamped &pos);
