#include <ros/ros.h>
#include <string>
#include "animal_msgs/dogMsg.h"
#include "animal_lib/Dog.h"

using  namespace std;

Dog::Dog(string Name, int Age, bool Sex, Breed BReed): Animal(Name, Age, Sex),breed(BReed){}

Dog::Dog(Dog male, Dog female): Animal(male.name, 0, rand() % 2){
    breed = male.breed;
    ROS_INFO("New puppy was born.");
}

Dog::Dog(animal_msgs::dogMsg &msg){
    breed = Breed(msg.breed);
    name = msg.name;
    sex = msg.sex;
    age = 0;
}

void Dog::set_message(animal_msgs::dogMsg &msg){
    msg.breed = breed;
    msg.name = name;
    msg.sex = sex;
    age = 0;
}
