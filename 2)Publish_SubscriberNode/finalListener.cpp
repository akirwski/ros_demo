#include <ros/ros.h>
#include <std_msgs/Int16.h>

using namespace std;

void chatterCallBackThree(const std_msgs::Int16::ConstPtr& msg){

    ROS_INFO("Final Listener heard %d", msg->data);
    cout << msg->data << endl;
}

int main(int argc, char**argv){

    ros::init(argc, argv, "finalListener");
    ros::NodeHandle n;
    ros::Subscriber subscriber = n.subscribe("response", 1000, chatterCallBackThree);

    ros::spin();

    return 0;

}
~    
