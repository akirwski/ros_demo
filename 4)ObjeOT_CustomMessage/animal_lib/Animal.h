
#ifndef ANIMAL_H
#define ANIMAL_H

#include <ros/ros.h>
#include <string>
#include <iostream>
#include "animal_msgs/dogMsg.h"
using  namespace std;

class Animal{
protected:
   string name;
   int age;
   bool sex;

 public:
   Animal(){};
   Animal(string Name, int Age, bool Sex);
   void introduceMyself();
};

#endif
