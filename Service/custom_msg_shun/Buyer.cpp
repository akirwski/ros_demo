#include <ros/ros.h>
#include <string>
#include "animal_srv/dogSrv.h"
#include "animal_lib/Dog.h"

using namespace std;

class Buyer{
  private:
    ros::NodeHandle n;
    animal_srv::dogSrv srv;
    ros::Timer buyTimer;
    ros::ServiceClient clientOne = n.serviceClient<animal_srv::dogSrv>("buyMaleDogs");
    ros::ServiceClient clientTwo = n.serviceClient<animal_srv::dogSrv>("buyFemaleDogs");
    Dog altDog;
  public:
    Buyer(){
      buyTimer = n.createTimer(ros::Duration(5.0), boost::bind(&Buyer::buyDog, this));
    }

    void buyDog();

};

void Buyer::buyDog(){
      altDog.set_service_request(srv);
      if(clientOne.call(srv)){
        string sex;
        if(srv.response.sex == true)
          sex = "female";
        else
          sex = "male";
        ROS_INFO("Buyer successfuly purchased a male dog. Name: %s Sex: %s  Age: %d Breed: %d", srv.response.name.c_str(), sex.c_str(), srv.response.age, srv.response.breed);
      } else {
        ROS_ERROR("Failed to call service buydogs");
      }

      if(clientTwo.call(srv)){
        string sex;
        if(srv.response.sex == true)
          sex = "female";
        else
          sex = "male";
        ROS_INFO("Buyer successfuly purchased a female dog. Name: %s Sex: %s  Age: %d Breed: %d", srv.response.name.c_str(), sex.c_str(), srv.response.age, srv.response.breed);
      } else {
        ROS_ERROR("Failed to call service buydogs");
      }
}

int main(int argc, char**argv){
  ros::init(argc, argv, "buyer");
  Buyer buyer;
  ros::spin();
  return 0;
}
