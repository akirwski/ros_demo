#include "animal_lib/Dog.h"

Dog::Dog(string Name, int Age, bool Sex, Breed BReed, ros::NodeHandle n): Animal(Name, Age, Sex),breed(BReed),lifetime(rand()%20){
    lifetimer = n.createTimer(ros::Duration(5.0), boost::bind(&Dog::getOlder, this));
}

Dog::Dog(Dog male, Dog female, ros::NodeHandle n): Animal(male.name, 0, rand() % 2), breed(female.breed),lifetime(rand()%20){
    lifetimer = n.createTimer(ros::Duration(5.0), boost::bind(&Dog::getOlder, this));
    ROS_INFO("New puppy was born.");
}

Dog::Dog(animal_msgs::dogMsg &msg, ros::NodeHandle n){
    breed = Breed(msg.breed);
    name = msg.name;
    sex = msg.sex;
    lifetime = msg.lifetime;
    lifetimer = n.createTimer(ros::Duration(5.0), boost::bind(&Dog::getOlder, this));
    age = 0;
}

Dog::Dog(const animal_msgs::dogMsg::ConstPtr& msg, ros::NodeHandle n){
    breed = Breed(msg->breed);
    name = msg->name;
    sex = msg->sex;
    lifetime = msg->lifetime;
    lifetimer = n.createTimer(ros::Duration(5.0), boost::bind(&Dog::getOlder, this));
    age = 0;
}

void Dog::set_message(animal_msgs::dogMsg &msg){
    msg.breed = breed;
    msg.name = name;
    msg.sex = sex;
    msg.lifetime = lifetime;
    age = 0;
}

void Dog::set_service_request( animal_srv::dogSrv &srv){
  srv.request.breed = breed;
  srv.request.sex = sex;
  srv.request.age = age;
  srv.request.name = name;
  srv.request.lifetime = lifetime;
}
