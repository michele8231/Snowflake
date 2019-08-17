/*
 * Created By: Ihsan Olawale
 * Created On: May 25, 2019
 * Description: An RF communication node that publishes messages
 * to the server node and listens for responses from the server.
 */

#ifndef RF_COMM_CLIENT_NODE_H
#define RF_COMM_CLIENT_NODE_H

// STD Includes
#include <iostream>

// ROS Includes
#include <std_msgs/String.h>
#include <ros/ros.h>

// Snowbots Includes
#include <sb_utils.h>

class RfCommClient {
public:
    RfCommClient(int argc, char **argv, std::string node_name);

private:
    /**
     * Callback function for when a new response is received
     *
     * @param msg the string received in the callback
     */
    void ClientResponseCallBack(const std_msgs::String::ConstPtr& command);
    /**
     * Publishes a given string
     *
     * @param command the string to publish
     */
    void ClientCommandCallBack(std::string command);
    /**
     * Helper function to create the published message
     */
    void createNextMessage();

    ros::Subscriber server_subscriber;
    ros::Publisher client_publisher;
};
#endif // RF_COMM_CLIENT_NODE_H
