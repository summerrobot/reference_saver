#include "position_logger.h"

/* 
struct Positions {
    double x;
    double y;
    double z;
};

*/

Angles convertQuternionToRollPitchYaw(const tf::StampedTransform &trans)
{
    Angles rollpitchyaw;

    tf::Quaternion q(trans.getRotation /* pos.pose.orientation.x, pos.pose.orientation.y,pos.pose.orientation.z, 
                      pos.pose.orientation.w*/);
    tf::Matrix3x3 m(q);
    m.getRPY(rollpitchyaw.roll,rollpitchyaw.pitch,rollpitchyaw.yaw);
    
    return rollpitchyaw;
}



void getPositionInputandWriteToFile(const tf::StampedTransform &trans )
{


    Angles rollpitchYaw{convertQuternionToRollPitchYaw(trans)};


    // Open file

    std::ofstream file{ "/home/" + USER +  "/Desktop/" + OUTPUTFILENAME + ".yaml" };


    if(!file)
    {
        cerr<<"Fault: File could not open"<<endl;
    }

    
    // Write position to file

    std::ostringstream sstream;
    sstream<< trans.getOrigin[0] << " " << trans.getOrigin[1] << " " 
    << trans.getOrigin[2] <<" "<< rollpitchYaw.yaw;

    string getValues{sstream.str()};

    file << getValues;

}


bool getPosition(std_srvs::Trigger::Response &position_response,
                std_srvs::Empty::Request &Xbox_button_request)
{

    geometry_msgs::PoseStamped pose;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    try{
      //TODO: Put in correct frames 
      listener.lookupTransform("map", "base_link",
                               ros::Time(0), transform);
      getPositionInputandWriteToFile(transform);    
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }







    //

}






