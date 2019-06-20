#pragma once

#include "ros/ros.h"
#include "std_srvs/Trigger.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_srvs/Empty.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tf/tf.h>
#include <stdlib.h>


using namespace std;

struct Angles {
    double roll;
    double pitch;
    double yaw;
};


char *user = getenv("USER");
std::string USER(user);
string OUTPUTFILENAME{"PostionLogger"};

bool getPosition(std_srvs::Trigger::Response &position_response,
                std_srvs::Empty::Request &Xbox_button_request);

void getPositionInputandWriteToFile(const geometry_msgs::PoseStamped &pos );
Angles convertQuternionToRollPitchYaw(const geometry_msgs::PoseStamped &pos);
