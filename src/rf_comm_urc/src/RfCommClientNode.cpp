/* 
 * Created By: Ihsan Olawale
 * Created On: May 25, 2019
 * Description: An RF communication node that publishes messages
 * to the server node and returns statuses in response.
 */

#include <utility>
#include <RfCommClientNode.h>
#include <sstream>

RfCommClient::RfCommClient(int argc, char **argv, std::string node_name) {
	ros::init(argc, argv, node_name);

	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");

	std::string publish_topic = private_nh.resolveName("client");
	int queue_size = 10;
	client_publisher = private_nh.advertise<std_msgs::String>(publish_topic, queue_size);

	std::string subscribe_topic = "rf_comm_server_node/server";
	queue_size = 10;
	server_subscriber = nh.subscribe(subscribe_topic, queue_size, &RfCommClient::ClientResponseCallBack, this);

	createNextMessage();
}

void RfCommClient::ClientResponseCallBack(const std_msgs::String::ConstPtr& command) {
	ROS_INFO("Received response");
	createNextMessage();
}

void RfCommClient::ClientCommandCallBack(std::string command) {
	std_msgs::String msg;
	msg.data = std::move(command);
	ROS_INFO("%s", msg.data.c_str());
	while (client_publisher.getNumSubscribers() <= 0) {
		// its too early to publish
	}
	client_publisher.publish(msg);
	ROS_INFO("Published message");
}

void RfCommClient::createNextMessage() {
	static int numMessages = 0;
	std::stringstream ss;
	ss << "client node publish #" << ++numMessages;
	ClientCommandCallBack(ss.str());
}
