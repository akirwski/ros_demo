#ifndef DOG_H
#define DOG_H

#include <ros/ros.h>
#include "animal_msgs/dogMsg.h"
#include <string>
#include "Animal.h"

using  namespace std;
enum Breed { A, B, C, D };

class Dog : public Animal {
private:
  Breed breed;

public:
  Dog(){}
  Dog(string Name, int Age, bool Sex, Breed BReed);
  Dog( Dog male, Dog female);
  Dog(animal_msgs::dogMsg &dog);
  //set message from this instance into the received object
  void set_message( animal_msgs::dogMsg &msg );

};

#endif
