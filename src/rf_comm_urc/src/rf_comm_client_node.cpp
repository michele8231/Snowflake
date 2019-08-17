#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
#include <RfCommClientNode.h>

int main(int argc, char **argv) {

	std::string node_name = "rf_comm_client_node";

	RfCommClient rf_comm_client(argc, argv, node_name);

	ros::spin();

	return 0;
}
