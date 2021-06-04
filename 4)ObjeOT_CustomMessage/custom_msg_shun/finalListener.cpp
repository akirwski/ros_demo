#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include <string>
using namespace std;

void chatterCallBackThree(const animal_msgs::dogMsg::ConstPtr& msg){
  string sex;
  if(msg->sex == true)
    sex = "female";
  else
    sex = "male";
  ROS_INFO("Received new dog. name: %s sex: %s breed: %d age: %d", msg->name.c_str(), sex.c_str(), msg->breed, msg->age);
}

int main(int argc, char**argv){

    ros::init(argc, argv, "finalListener");
    ros::NodeHandle n;
    ros::Subscriber subscriber = n.subscribe("response", 1000, chatterCallBackThree);

    ros::spin();

    return 0;

}
