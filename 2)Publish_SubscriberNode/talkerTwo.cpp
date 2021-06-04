#include <ros/ros.h>
#include <std_msgs/Int16.h>

using namespace std;

int main(int argc, char**argv){

    ros::init(argc, argv, "talkerTwo");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<std_msgs::Int16>("chatTwo", 1000);
    ros::Rate rate(1);

    while(ros::ok()){
        std_msgs::Int16 msg;

        int ss = rand() % 10;
        msg.data = ss;
        ROS_INFO("%d", msg.data);

        publisher.publish(msg);

        rate.sleep();
    }

    return 0;

}
