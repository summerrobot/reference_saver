#include "position_logger.hpp"

int main(int argc, char **argv)
{

    ros::init(argc, argv, "get_position_server" );
    ros::NodeHandle get_position_node;

    ros::ServiceServer service = get_position_node.advertiseService("get_position", getPosition);

    ROS_INFO("Ready to write position to file");
    ros::spin();


    return 0;
}