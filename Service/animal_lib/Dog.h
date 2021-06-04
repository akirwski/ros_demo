#ifndef DOG_H
#define DOG_H

#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include "animal_srv/dogSrv.h"
#include <string>
#include "Animal.h"
using namespace std;
enum Breed { A, B, C, D };

class Dog : public Animal {
private:
  Breed breed;
  int lifetime;
  ros::Timer lifetimer;

public:
  Dog(){}
  Dog(string Name, int Age, bool Sex, Breed BReed, ros::NodeHandle n);
  Dog( Dog male, Dog female, ros::NodeHandle n);
  Dog(animal_msgs::dogMsg &dog, ros::NodeHandle n);
  Dog(const animal_msgs::dogMsg::ConstPtr &dog, ros::NodeHandle n);
  //set message from this instance into the received object
  void set_message( animal_msgs::dogMsg &msg );
  void set_service_request( animal_srv::dogSrv &srv);
  void set_service_response( animal_srv::dogSrv::Request & req, animal_srv::dogSrv::Response & res);
  int get_age();
  int get_lifetime();
  void getOlder();
};

#endif
