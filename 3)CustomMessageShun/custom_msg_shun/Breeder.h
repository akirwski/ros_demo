#ifndef LISTENER_CLASS_H
#define LISTENER_CLASS_HP

#include <ros/ros.h>
#include "dog_msgs/dogMsg.h"
#include <string>

using namespace std;

class Breeder {
    private:
    ros::Subscriber subOne;
    ros::Subscriber subTwo;
    ros::Publisher pub;
    ros::NodeHandle n;
    ros::Timer publishTimer;

    dog_msgs::dogMsg receivedMaleDog;
    dog_msgs::dogMsg receivedFemaleDog;

    public:
    Breeder(){}
    Breeder(string subTopicOne, string subTopicTwo, string pubTopic){
        subOne = n.subscribe<dog_msgs::dogMsg>(subTopicOne, 1000, &Breeder::chatterCallBackOne, this );
        subTwo = n.subscribe<dog_msgs::dogMsg>(subTopicTwo, 1000, &Breeder::chatterCallBackTwo, this );
        pub = n.advertise<dog_msgs::dogMsg>(pubTopic, 1000);
        publishTimer = n.createTimer( ros::Duration(1.0), boost::bind( &Breeder::publishResponse, this ) );
    }

    ros::NodeHandle& get_n(){ return n; }
    void chatterCallBackOne(const typename dog_msgs::dogMsg::ConstPtr& receivedMsg); //receiving message as pointer
    void chatterCallBackTwo(const typename dog_msgs::dogMsg::ConstPtr& receivedMsg);
    void publishResponse();
    dog_msgs::dogMsg createNewDog();

};

void Breeder::chatterCallBackOne(const dog_msgs::dogMsg::ConstPtr& receivedMsg)
{
    ROS_INFO("I received new name = %s from talkerOne", receivedMsg->name.c_str());
    receivedMaleDog = *receivedMsg;

}

void Breeder::chatterCallBackTwo(const dog_msgs::dogMsg::ConstPtr& receivedMsg){
     receivedFemaleDog = *receivedMsg;

     ROS_INFO("I received new breed = %d from talkerTwo", receivedMsg->breed);

}

dog_msgs::dogMsg  Breeder::createNewDog(){
    dog_msgs::dogMsg newDog;
    newDog.name = receivedMaleDog.name;
    newDog.breed = receivedFemaleDog.breed;
    newDog.age = rand() % 20;
    newDog.sex = rand() % 2;
    
    void  Breeder::publishResponse(){
    dog_msgs::dogMsg response = createNewDog();
    string sex;
    if(response.sex == true)
      sex = "female";
    else
      sex = "male";
    ROS_INFO("ListnerClass: Publishing new dog. name: %s sex: %s breed: %d age: %d", response.name.c_str(), sex.c_str(), response.breed, response.age);
    pub.publish(response);
}

#endif
