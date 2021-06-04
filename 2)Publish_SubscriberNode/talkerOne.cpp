#include <ros/ros.h>
#include <std_msgs/Bool.h>


using namespace std;

int main(int argc, char** argv){

    ros::init(argc, argv, "talkerOne");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<std_msgs::Bool>("chatOne", 1000);
    ros::Rate loop_rate(1);

    while(ros::ok()){
        std_msgs::Bool msg;

        bool ss = rand() % 2;
        msg.data = ss;
        if (ss)
            ROS_INFO("true");
        else
            ROS_INFO("false");

        publisher.publish(msg);

        loop_rate.sleep();
    }

    return 0;

}
