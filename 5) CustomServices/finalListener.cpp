#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include "animal_lib/Dog.h"
#include <string>
#include <vector>
using namespace std;


class FinalListener {
private:
  ros::NodeHandle n;
  ros::Subscriber subscriber;
  ros::Subscriber subPrinter;
  ros::Publisher publisherMale;
  ros::Publisher publisherFemale;
  ros::Timer sendBackTimer;
  vector<Dog> vecMaleDogs;
  vector<Dog> vecFemaleDogs;

public:
  FinalListener(){
    subscriber = n.subscribe<animal_msgs::dogMsg>("response", 1000, &FinalListener::chatterCallBackThree, this);
    publisherMale = n.advertise<animal_msgs::dogMsg>("sendBackMale", 1000);
    publisherFemale = n.advertise<animal_msgs::dogMsg>("sendBackFemale", 1000);
    sendBackTimer = n.createTimer(ros::Duration(1.0), boost::bind(&FinalListener::sendBack, this));
    subPrinter = n.subscribe("printVec", 1000, &FinalListener::chatterCallBackPrint, this);
  }
  void sendBack();
  void chatterCallBackThree(const animal_msgs::dogMsg::ConstPtr& msg);
  void chatterCallBackPrint(const animal_msgs::Int16& receivedMsg);
};

void FinalListener::chatterCallBackThree(const animal_msgs::dogMsg::ConstPtr& msg){
  Dog newBornDog(msg, n);
  string sex;
  if(msg->sex == true){
    sex = "female";
    vecFemaleDogs.push_back(newBornDog);
  } else {
    sex = "male";
    vecMaleDogs.push_back(newBornDog);
  }
//  ROS_INFO("Received new dog. name: %s sex: %s breed: %d age: %d", msg->name.c_str(), sex.c_str(), msg->breed, msg->age);
}



void FinalListener::sendBack(){
  for(int i=0; i< vecMaleDogs.size(); i++){
    if(vecMaleDogs[i].get_age() > 0){
      animal_msgs::dogMsg msg;
      vecMaleDogs[i].set_message(msg);
      publisherMale.publish(msg);
    }
  }

  for(int i=0; i<vecFemaleDogs.size(); i++){
    if(vecFemaleDogs[i].get_age() > 0){
      animal_msgs::dogMsg msg;
      vecFemaleDogs[i].set_message(msg);
      publisherFemale.publish(msg);
    }
  }
}

void FinalListener::chatterCallBackPrint(const animal_msgs::Int16& receivedMsg){
  for(vector<Dog>::iterator it=vecMaleDogs.begin(); it!=vecMaleDogs.end(); it++){
    it->print();
 }
  for(vector<Dog>::iterator it=vecFemaleDogs.begin(); it!=vecFemaleDogs.end(); it++){
    it->print()
  }
}

int main(int argc, char**argv){
    ros::init(argc, argv, "finalListener");
    FinalListener finalListener;
    ros::spin();
    return 0;

}
