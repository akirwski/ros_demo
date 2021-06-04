#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include "animal_lib/Dog.h"
#include <string>
using namespace std;

int main(int argc, char**argv){

  ros::init(argc, argv, "talkerTwo");
  ros::NodeHandle n;
  ros::Publisher publisher = n.advertise<animal_msgs::dogMsg>("chatTwo", 1000);
  ros::Rate loop_rate(1);

  while(ros::ok()){
      animal_msgs::dogMsg msg;

      string nameList[] = {"Maggy", "Maddison", "Ally", "Christina"};
      Dog newfemaleDog(nameList[(rand() % 4)], rand() % 20, true, Breed(rand() % 5));
      newfemaleDog.set_message(msg);

      ROS_INFO("Created Female dog. name: %s age: %d breed: %d . ", msg.name.c_str(), msg.age, msg.breed);

      publisher.publish(msg);
      loop_rate.sleep();

    }
    return 0;

}
