#ifndef LISTENER_CLASS_H
#define LISTENER_CLASS_HP

#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include "animal_msgs/catMsg.h"
#include <string>
#include "animal_lib/Dog.h"

using namespace std;

class Breeder {
    private:
    ros::Subscriber subOne;
    ros::Subscriber subTwo;
    ros::Publisher pub;
    ros::NodeHandle n;
    ros::Timer publishTimer;

    Dog maleDog;
    Dog femaleDog;

    public:
    Breeder(string subTopicOne, string subTopicTwo, string pubTopic){
        subOne = n.subscribe<animal_msgs::dogMsg>(subTopicOne, 1000, &Breeder::chatterCallBackOne, this );
        subTwo = n.subscribe<animal_msgs::dogMsg>(subTopicTwo, 1000, &Breeder::chatterCallBackTwo, this );
        pub = n.advertise<animal_msgs::dogMsg>(pubTopic, 1000);
        publishTimer = n.createTimer( ros::Duration(1.0), boost::bind( &Breeder::publishResponse, this ) );
    }

    ros::NodeHandle& get_n(){ return n; }
    void chatterCallBackOne(const typename animal_msgs::dogMsg::ConstPtr& receivedMsg); //receiving message as pointer
    void chatterCallBackTwo(const typename animal_msgs::dogMsg::ConstPtr& receivedMsg);
    void publishResponse();

};

void Breeder::chatterCallBackOne(const animal_msgs::dogMsg::ConstPtr& receivedMsg)
{
    ROS_INFO("I received new name = %s from talkerOne", receivedMsg->name.c_str());

    //this is costPtr$ dog message, convert it into simple dog message
    Dog newMaleDog(receivedMsg);
    maleDog = newMaleDog;

}

void Breeder::chatterCallBackTwo(const animal_msgs::dogMsg::ConstPtr& receivedMsg){
     ROS_INFO("I received new breed = %d from talkerTwo", receivedMsg->breed);
     Dog newMaleDog(receivedMsg);
     femaleDog = newMaleDog;
}


void  Breeder::publishResponse(){
    animal_msgs::dogMsg response;
    Dog childDog(maleDog, femaleDog);

    //in the response message, set information from childDog
    childDog.set_message(response);

    string sex;
    if(response.sex == true)
      sex = "female";
    else
      sex = "male";
    ROS_INFO("ListnerClass: Publishing new dog. name: %s sex: %s breed: %d age: %d", response.name.c_str(), sex.c_str(), response.breed, response.age);

    pub.publish(response);
}

#endif
