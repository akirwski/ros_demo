#ifndef LISTENER_CLASS_H
#define LISTENER_CLASS_H

#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include "animal_msgs/dogsMsg.h"
#include "animal_msgs/catMsg.h"
#include <string>
#include <vector>
#include "animal_lib/Dog.h"

using namespace std;

class Breeder {
    private:
    ros::Subscriber subOne;
    ros::Subscriber subTwo;
    ros::Publisher pub;
    ros::NodeHandle n;
    ros::Timer publishTimer;
    ros::Timer birthTimer;

    vector<Dog> maleVec;
    vector<Dog> femaleVec;

    public:
    Breeder(string subTopicOne, string subTopicTwo, string pubTopic){
        subOne = n.subscribe<animal_msgs::dogsMsg>(subTopicOne, 1000, &Breeder::chatterCallBackOne, this );
        subTwo = n.subscribe<animal_msgs::dogsMsg>(subTopicTwo, 1000, &Breeder::chatterCallBackTwo, this );
        pub = n.advertise<animal_msgs::dogMsg>(pubTopic, 1000);
        publishTimer = n.createTimer( ros::Duration(3.0), boost::bind( &Breeder::publishResponse, this));
    }

    ros::NodeHandle& get_n(){ return n; }
    void chatterCallBackOne(const animal_msgs::dogsMsg::ConstPtr& receivedMsg); //receiving message as pointer
    void chatterCallBackTwo(const animal_msgs::dogsMsg::ConstPtr& receivedMsg);
    void publishResponse();

};

void Breeder::chatterCallBackOne(const animal_msgs::dogsMsg::ConstPtr& receivedMsg)
{
    ROS_INFO("I received new vector of Male dogs");
    for(int i=0; i<receivedMsg->dogs.size(); i++){
       animal_msgs::dogMsg msg = receivedMsg->dogs[i];
       Dog newMaleDog(msg, n);
       maleVec.push_back(newMaleDog);
    }
}

void Breeder::chatterCallBackTwo(const animal_msgs::dogsMsg::ConstPtr& receivedMsg){
     ROS_INFO("I received new vector of Female dogs");
      for(int i=0; i<receivedMsg->dogs.size(); i++){
       animal_msgs::dogMsg msg = receivedMsg->dogs[i];
       Dog newFemaleDog(msg, n);
       femaleVec.push_back(newFemaleDog);
    }
}

void  Breeder::publishResponse(){
    ROS_INFO("publishing a child dog to the finalListener");
    animal_msgs::dogMsg response;
    Dog male = maleVec[rand()%maleVec.size()];
    Dog female = femaleVec[rand()%femaleVec.size()];
    Dog childDog(male, female, n);
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
