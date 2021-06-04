#include <ros/ros.h>
#include "ListenerClass.h"
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>

using namespace std;

template<>
void ListenerClass<std_msgs::Bool, std_msgs::Int16, std_msgs::Int16>::chatterCallBackOne(const std_msgs::Bool::ConstPtr& receivedMsg)
{
    string a;
    if(receivedMsg->data == true){
        a = "true";
    }else{
        a = "false";
    }
    ROS_INFO("I received bool = %s from talkerOne", a.c_str());
    receivedOne = receivedMsg->data;

}

template<>
void ListenerClass<std_msgs::Bool, std_msgs::Int16, std_msgs::Int16>::chatterCallBackTwo(const std_msgs::Int16::ConstPtr& receivedMsg){
     receivedTwo = receivedMsg->data;

     ROS_INFO("I received number = %d from talkerTwo", receivedTwo);

}

template<>
int  ListenerClass<std_msgs::Bool, std_msgs::Int16, std_msgs::Int16>::calculate(){
    if(receivedOne == true) return receivedTwo  * 2;
    return receivedTwo * -1;
}

template<>
void  ListenerClass<std_msgs::Bool, std_msgs::Int16, std_msgs::Int16>::publishResponse(){
    int response = calculate();
    std_msgs::Int16 msg;
    cout << response << "をoutputしたよ"<< endl;
    msg.data = response;
    ROS_INFO("ListnerClass: Publishing %d", msg.data);
    pub.publish(msg);
}


int main(int argc, char **argv){
    ros::init(argc, argv, "ListenerClass");
    ListenerClass<std_msgs::Bool, std_msgs::Int16, std_msgs::Int16> listener("chatOne", "chatTwo", "response");

    ros::spin();
}
