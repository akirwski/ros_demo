#include <ros/ros.h>
#include "Breeder.h"
#include "animal_lib/Animal.h"
#include "animal_lib/Dog.h"
#include "animal_lib/Cat.h"
using namespace std;

int main(int argc, char **argv){

    ros::init(argc, argv, "breeder");
    Breeder listener("chatOne", "chatTwo", "response");

    ros::spin();

}
