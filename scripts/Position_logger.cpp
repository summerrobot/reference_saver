#include "position_logger.hpp"

/* 
struct Positions {
    double x;
    double y;
    double z;
};

*/


string OUTPUTFILENAME{"PostionLogger"};


Angles convertQuternionToRollPitchYaw(const tf::StampedTransform &trans)
{
    Angles rollpitchyaw;

    tf::Quaternion q(trans.getRotation());
    tf::Matrix3x3 m(q);
    m.getRPY(rollpitchyaw.roll,rollpitchyaw.pitch,rollpitchyaw.yaw);
    
    return rollpitchyaw;
}



void getPositionInputandWriteToFile(const tf::StampedTransform &trans )
{


    Angles rollpitchYaw{convertQuternionToRollPitchYaw(trans)};


    const char* home = getenv("USER");

    if (!home)
    {
        std::cerr << "USER is not defined." << std::endl;
    }

    std::string USER_STRING = home;

    // Open file

    std::ofstream file{ "/home/" + USER_STRING +  "/Desktop/" + OUTPUTFILENAME + ".yaml" };


    if(!file)
    {
        cerr<<"Fault: File could not open"<<endl;
    }

    
    // Write position to file

    std::ostringstream sstream;
    sstream<< trans.getOrigin().getX() << " " << trans.getOrigin().getY() << " " 
    << trans.getOrigin().getZ() <<" "<< rollpitchYaw.yaw;

    string getValues{sstream.str()};

    file << getValues;

}


bool getPosition(std_srvs::Trigger::Response &position_response,
                std_srvs::Trigger::Request &Xbox_button_request)
{

    /* 
 
    geometry_msgs::PoseStamped pose;

    tf::TransformListener listener;
    ros::Rate rate(10.0);
    while (true)
    {
        tf::StampedTransform transform;
        try{
      //TODO: Put in correct frames 
            listener.lookupTransform("map", "base_link",
                               ros::Time(0), transform);
            //getPositionInputandWriteToFile(transform);
            position_response.message = "Success: Pose stored to file";
            position_response.success = true; 
            return true;   
    }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            position_response.message = "Fault: Pose not stored to file";
            position_response.success = false;
            continue;
            return false;
        }
        rate.sleep();   
    }

    */
}






