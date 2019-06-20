#include "position_logger.h"

/* 
struct Positions {
    double x;
    double y;
    double z;
};

*/

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

    std::ofstream file{ "/home/" + USER +  "/Desktop/" + OUTPUTFILENAME + ".yaml" };


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
    tf::TransformListener listener;
    tf::StampedTransform transform;

    try{
      //TODO: Put in correct frames 
      listener.lookupTransform("map", "base_link",
                               ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

    getPositionInputandWriteToFile(position);






    //

}






