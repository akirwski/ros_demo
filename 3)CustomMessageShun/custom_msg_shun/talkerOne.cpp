#include <ros/ros.h>
#include "dog_msgs/dogMsg.h"
#include <string>

using namespace std;

int main(int argc, char** argv){

    ros::init(argc, argv, "talkerOne");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<dog_msgs::dogMsg>("chatOne", 1000);
    ros::Rate loop_rate(1);

    while(ros::ok()){
        dog_msgs::dogMsg msg;

        string nameList[] = {"Pochi", "Sam", "Gabby", "Teddy"};
        string createdName = nameList[(rand() % 4)];
        int createdAge = rand();
        int createdBreed = rand() % 5;
        msg.sex = false;
        msg.name = createdName;
        msg.age = createdAge;
        msg.breed = createdBreed;


        ROS_INFO("Created Male dog. name: %s age: %d breed: %d . ", msg.name.c_str(), msg.age, msg.breed);


        publisher.publish(msg);

        loop_rate.sleep();
    }

    return 0;

}
