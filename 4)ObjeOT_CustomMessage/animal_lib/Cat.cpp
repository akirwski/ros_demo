#include <ros/ros.h>
#include <string>
#include "animal_lib/Cat.h"
using namespace std;

Cat::Cat(string Name, int Age, bool Sex, HomeCountry Country):Animal(Name, Age, Sex), homecountry(Country){}
