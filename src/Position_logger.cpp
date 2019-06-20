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


char *user = getenv("USER");
std::string str(user);
string OUTPUTFILENAME{"PostionLogger"};

/* 
struct Positions {
    double x;
    double y;
    double z;
};

*/

struct Angles {
    double roll;
    double pitch;
    double yaw;
};

Angles convertQuternionToRollPitchYaw(const geometry_msgs::PoseStamped &pos)
{
    Angles rollpitchyaw;

    tf::Quaternion q(pos.pose.orientation.x, pos.pose.orientation.y,pos.pose.orientation.z, pos.pose.orientation.w);
    tf::Matrix3x3 m(q);
    m.getRPY(rollpitchyaw.roll,rollpitchyaw.pitch,rollpitchyaw.yaw);
    
    return rollpitchyaw;
}



void getPositionInputandWriteToFile(const geometry_msgs::PoseStamped &pos )
{


    Angles rollpitchYaw{convertQuternionToRollPitchYaw(pos)};


    // Open file

    std::ofstream file{ "/home/" + str +  "/Desktop/" + OUTPUTFILENAME + ".yaml" };


    if(!file)
    {
        cerr<<"Fault: File could not open"<<endl;
    }

    
    // Write position to file

    std::ostringstream sstream;
    sstream<< pos.pose.position.x << " " << pos.pose.position.y << " " << pos.pose.position.z <<" "<< rollpitchYaw.yaw;

    string getValues{sstream.str()};

    file << getValues;

}


bool getPosition(std_srvs::Trigger::Response &position_response,
                std_srvs::Empty::Request &Xbox_button_request)
{

    geometry_msgs::PoseStamped position;

    getPositionInputandWriteToFile(position);

}


int main(int argc, char **argv)
{

    ros::init(argc, argv, "get_position_server" );
    ros::NodeHandle get_position_node;

    ros::ServiceServer service = get_position_node.advertiseService("log_position", getPosition);


    ROS_INFO("Ready to write position to file");
    ros::spin();


    return 0;
}