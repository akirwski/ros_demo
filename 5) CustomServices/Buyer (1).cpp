#include <ros/ros.h>
#include <string>
#include <vector>
#include "animal_srv/dogSrv.h"
#include "animal_lib/Dog.h"

using namespace std;

class Buyer{
  private:
    ros::NodeHandle n;
    animal_srv::dogSrv srv;
    ros::Timer buyTimer;
    ros::ServiceClient clientOne;
    ros::ServiceClient clientTwo;
    ros::Subscriber sub;
    Dog altDog;
    vector<Dog> purchasedDogsVec;
  public:
    Buyer(){
      buyTimer = n.createTimer(ros::Duration(5.0), boost::bind(&Buyer::buyDog, this));
      clientOne = n.serviceClient<animal_srv::dogSrv>("buyMaleDogs");
      clientTwo = n.serviceClient<animal_srv::dogSrv>("buyFemaleDogs");
      sub = n.subscribe("printVec", 1000, &Buyer::chatterCallBackPrint, this);
    }
    void buyDog();
    void chatterCallBackPrint(const animal_msgs::Int16& receivedMsg);

};

void Buyer::buyDog(){
      altDog.set_service_request(srv);
      if(clientOne.call(srv)){
        string sex;
        if(srv.response.sex == true)
          sex = "female";
        else
          sex = "male";
        //ROS_INFO("Buyer successfuly purchased a male dog. Name: %s Sex: %s  Age: %d Breed: %d", srv.response.name.c_str(), sex.c_str(), srv.response.age, srv.response.breed);
        Dog purchasemale(srv, n);

        purchasedDogsVec.push_back(purchasedmale);
      } else {
        //ROS_ERROR("Failed to call service buydogs");
      }

      if(clientTwo.call(srv)){
        string sex;
        if(srv.response.sex == true)
          sex = "female";
        else
          sex = "male";
        //ROS_INFO("Buyer successfuly purchased a female dog. Name: %s Sex: %s  Age: %d Breed: %d", srv.response.name.c_str(), sex.c_str(), srv.response.age, srv.response.breed);
        Dog purchasefemale(srv, n);
        purchasedDogsVec.push_back(purchasedfemale);
      } else {
        //ROS_ERROR("Failed to call service buydogs");
      }
}
void Buyer::chatterCallBackPrint(const animal_msgs::Int16& receivedMsg){
  for(vector<Dog>::iterator it=purchasedDogsVec.begin(); it!=purchasedDogsVec.end(); it++){
    it->print();
    num++;
  }
}

int main(int argc, char**argv){
  ros::init(argc, argv, "buyer");
  Buyer buyer;
  ros::spin();
  return 0;
}
