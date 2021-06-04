#include <ros/ros.h>
#include <string>
#include <vector>
#include "animal_lib/Dog.h"
#include "animal_msgs/dogMsg.h"
#include "animal_msgs/dogsMsg.h"
#include "animal_srv/dogSrv.h"

using namespace std;

class MaleCreator{
  private:
    vector<Dog> maleDogsVec;
    ros::NodeHandle n;
    ros::Timer createDogTimer;
    ros::Timer sendTimer;
    ros::Timer getOlderTimer;
    ros::Publisher publisher;
    ros::Subscriber subscriber;
    ros::ServiceServer service;

  public:
    MaleCreator(){
       createDogTimer = n.createTimer(ros::Duration(1.0), boost::bind(&MaleCreator::createMaleDog, this));
       sendTimer = n.createTimer(ros::Duration(2.0), boost::bind(&MaleCreator::sendDogs, this));
       getOlderTimer = n.createTimer(ros::Duration(5.0), boost::bind(&MaleCreator::checkLifeTime, this));

       publisher = n.advertise<animal_msgs::dogsMsg>("chatOne", 1000);
       subscriber = n.subscribe<animal_msgs::dogMsg>("sendBackMale", 1000, &MaleCreator::chatterCallBackMale, this);
       service = n.advertiseService("buyMaleDogs", &MaleCreator::sellDog, this);
    }
    void createMaleDog();
    void sendDogs();
    void checkLifeTime();
    void chatterCallBackMale(const animal_msgs::dogMsg::ConstPtr& msg);
    bool sellDog(animal_srv::dogSrv::Request &req, animal_srv::dogSrv::Response &res);

};
void MaleCreator::createMaleDog(){
  string nameList[] = {"Pochi", "Sam", "Gabby", "Teddy"};
  Dog newMaleDog(nameList[(rand() % 4)], rand() % 20, false, Breed(rand() % 5), n);
  maleDogsVec.push_back(newMaleDog);
  ROS_INFO("Created Male dog.");
}

void MaleCreator::sendDogs(){
  ROS_INFO("Sending a vector of male dogs.");
  animal_msgs::dogsMsg vecMsg;
  for(int i=0; i<maleDogsVec.size(); i++){
    animal_msgs::dogMsg msg;
    maleDogsVec[i].set_message(msg);
    vecMsg.dogs.push_back(msg);
  }
  publisher.publish(vecMsg);
}

void MaleCreator::checkLifeTime(){
   ROS_INFO("Deleting the male over 20 year old dog.");
  for(vector<Dog>::iterator it=maleDogsVec.begin(); it!=maleDogsVec.end(); it++){
    if(it->get_age() > 20 )
      it = maleDogsVec.erase(it);
  }
}

void MaleCreator::chatterCallBackMale(const animal_msgs::dogMsg::ConstPtr& msg){
  Dog receivedMale(msg, n);
  maleDogsVec.push_back(receivedMale);
  ROS_INFO("Received male dog from finalListener");
}

bool MaleCreator::sellDog(animal_srv::dogSrv::Request &req, animal_srv::dogSrv::Response &res){
  Dog dog = maleDogsVec[rand()%maleDogsVec.size()];
  dog.set_service_response(req, res);
  ROS_INFO("Sold a  male dog as a response: Name[%s] Age[%d] Breed[%d] Lifetime[%d]", res.name.c_str(), res.age, res.breed, res.lifetime);
  return 1;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "talkerOne");
  MaleCreator maleCreator;
  ros::spin();
  return 0;
}
