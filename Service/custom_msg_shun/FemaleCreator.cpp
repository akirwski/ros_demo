#include <ros/ros.h>
#include <string>
#include <vector>
#include "animal_lib/Dog.h"
#include "animal_msgs/dogMsg.h"
#include "animal_msgs/dogsMsg.h"
#include "animal_srv/dogSrv.h"

using namespace std;

class FemaleCreator{
  private:
    vector<Dog> femaleDogsVec;
    ros::NodeHandle n;
    ros::Timer createDogTimer;
    ros::Timer sendTimer;
    ros::Timer getOlderTimer;
    ros::Publisher publisher;
    ros::Subscriber subscriber;
    ros::ServiceServer service;

  public:
    FemaleCreator(){
       createDogTimer = n.createTimer(ros::Duration(1.0), boost::bind(&FemaleCreator::createFemaleDog, this));
       sendTimer = n.createTimer(ros::Duration(2.0), boost::bind(&FemaleCreator::sendDogs, this));
       getOlderTimer = n.createTimer(ros::Duration(5.0), boost::bind(&FemaleCreator::checkLifeTime, this));

       publisher = n.advertise<animal_msgs::dogsMsg>("chatTwo", 1000);
       subscriber = n.subscribe<animal_msgs::dogMsg>("sendBackFemale", 1000, &FemaleCreator::chatterCallBackFemale, this);
       service = n.advertiseService("buyFemaleDogs", &FemaleCreator::sellDog, this);
    }
    void createFemaleDog();
    void sendDogs();
    void checkLifeTime();
    void chatterCallBackFemale(const animal_msgs::dogMsg::ConstPtr& msg);
    bool sellDog(animal_srv::dogSrv::Request &req, animal_srv::dogSrv::Response &res);
};

void FemaleCreator::createFemaleDog(){
  string nameList[] = {"Pochi", "Sam", "Gabby", "Teddy"};
  Dog newFemaleDog(nameList[(rand() % 4)], rand() % 20, true, Breed(rand() % 5), n);
  femaleDogsVec.push_back(newFemaleDog);
  ROS_INFO("Created Female dog");
}

void FemaleCreator::sendDogs(){
  ROS_INFO("Sending a vector of female dogs.");
  animal_msgs::dogsMsg vecMsg;
  for(int i=0; i<femaleDogsVec.size(); i++){
    animal_msgs::dogMsg msg;
    femaleDogsVec[i].set_message(msg);
    vecMsg.dogs.push_back(msg);
  }
  publisher.publish(vecMsg);
}

void FemaleCreator::checkLifeTime(){
  ROS_INFO("Deleted a over 20 year old female dog.");
  for(vector<Dog>::iterator it=femaleDogsVec.begin(); it!=femaleDogsVec.end(); it++){
    if(it->get_age() > 20 )
      it = femaleDogsVec.erase(it);
  }
}

void FemaleCreator::chatterCallBackFemale(const animal_msgs::dogMsg::ConstPtr& msg){
  Dog receivedFemale(msg, n);
  femaleDogsVec.push_back(receivedFemale);
  ROS_INFO("Received female dog from finalListener");
}

bool FemaleCreator::sellDog(animal_srv::dogSrv::Request &req, animal_srv::dogSrv::Response &res){
  Dog dog = femaleDogsVec[rand()%femaleDogsVec.size()];
  dog.set_service_response(req, res);
  ROS_INFO("Sold a female dog as a response: Name[%s] Age[%d] Breed[%d] Lifetime[%d]", res.name.c_str(), res.age, res.breed, res.lifetime);
}
int main(int argc, char** argv){
  ros::init(argc, argv, "talkerTwo");
  FemaleCreator femaleCreator;
  ros::spin();
  return 0;
}
