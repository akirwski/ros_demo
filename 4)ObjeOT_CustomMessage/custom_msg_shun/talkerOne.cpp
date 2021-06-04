#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include "animal_lib/Dog.h"
#include <string>

using namespace std;

int main(int argc, char** argv){

    ros::init(argc, argv, "talkerOne");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<animal_msgs::dogMsg>("chatOne", 1000);
    ros::Rate loop_rate(1);

    while(ros::ok()){
        animal_msgs::dogMsg msg;

        string nameList[] = {"Pochi", "Sam", "Gabby", "Teddy"};
        Dog newMaleDog(nameList[(rand() % 4)], rand() % 20, false, Breed(rand() % 5));
        newMaleDog.set_message(msg);

        ROS_INFO("Created Male dog. name: %s age: %d breed: %d . ", msg.name.c_str(), msg.age, msg.breed);

        publisher.publish(msg);

        loop_rate.sleep();
    }

    return 0;

}
