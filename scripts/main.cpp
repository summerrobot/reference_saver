#include "position_logger.hpp"

bool add (std_srvs::Trigger::Response &position_response,
                std_srvs::Trigger::Request &Xbox_button_request)
{
    return true;
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "get_position_server" );
    ros::NodeHandle get_position_node;

    ros::ServiceServer service = get_position_node.advertiseService("get_position", add);

    ROS_INFO("Ready to write position to file");
    ros::spin();


    return 0;
}