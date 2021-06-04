#include "animal_lib/Animal.h"

Animal::Animal(string Name, int Age, bool Sex): name(Name), age(Age), sex(Sex){}

void Animal::introduceMyself(){
  string s;
  if(sex == true)
    s = "female";
  else
    s = "male";
  ROS_INFO("Name: %s Age: %d, Sex: %s", name.c_str(), age, s.c_str());
}
